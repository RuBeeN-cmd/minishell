/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:09:17 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 18:03:20 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_interrupt;

void	sigint_during_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		g_interrupt = 3;
	}
}

void	remove_signal_handlers_for_heredocs(void)
{
	signal(SIGINT, &sigint_during_heredoc);
}

void	create_all_heredocs(t_shell *shell, t_cmd_element *list)
{
	t_cmd_element	*current;
	t_tmpfile		*new;
	t_tmpfile		*cur_tmp;
	int				ret;

	current = list;
	ret = 0;
	while (current && !ret)
	{
		if (current->type == REDIRECT && !ft_strcmp(current->str, "<<")
			&& !shell->interrupt)
		{
			new = create_heredoc(shell, current->next->str, list);
			if (!shell->tmpfile_list)
				shell->tmpfile_list = new;
			else
			{
				cur_tmp = shell->tmpfile_list;
				while (cur_tmp->next)
					cur_tmp = cur_tmp->next;
				cur_tmp->next = new;
			}
		}
		current = current->next;
	}
}

t_tmpfile	*create_heredoc(t_shell *shell, char *endredir, t_cmd_element *list)
{
	t_tmpfile	*new_tmpfile;
	pid_t		pid;
	int			status;

	new_tmpfile = init_tmpfile(find_unused_filename());
	new_tmpfile->fd = open(new_tmpfile->name, O_CREAT | O_RDWR | O_EXCL, 0777);
	if (new_tmpfile->fd == -1)
		perror("open:");
	if (new_tmpfile->fd == -1)
		return (new_tmpfile);
	remove_signal_handlers();
	pid = fork();
	shell->fork = 1;
	if (!pid)
		heredoc_fork(shell, new_tmpfile, endredir, list);
	shell->fork = 0;
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 3)
		shell->interrupt = 1;
	if (WEXITSTATUS(status) == 3)
		shell->exit_status = 130;
	set_signal_handlers();
	close(new_tmpfile->fd);
	return (new_tmpfile);
}

int	heredoc_fork(t_shell *shell, t_tmpfile *new_tmpfile, char *endredir,
		t_cmd_element *list)
{
	char	*line;

	remove_signal_handlers_for_heredocs();
	g_interrupt = 0;
	line = readline("");
	while (line && ft_strcmp(line, endredir) != 0)
	{
		ft_printf_fd(new_tmpfile->fd, line);
		ft_printf_fd(new_tmpfile->fd, "\n");
		free(line);
		line = readline("");
	}
	if (!line && !g_interrupt)
		ft_printf_fd(2,
			"warning : here-document delimited by EOF(wanted '%s')\n",
			endredir);
	else if (line)
		free(line);
	close(new_tmpfile->fd);
	free(new_tmpfile->name);
	free(new_tmpfile);
	destroy_element_list(list);
	destroy_tshell(shell);
	exit(g_interrupt);
}
