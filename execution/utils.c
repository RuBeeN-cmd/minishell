/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:58:14 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/11 18:25:57 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_new_line(int fd, char *line)
{
	ft_printf_fd(fd, line);
	ft_printf_fd(fd, "\n");
	free(line);
	return (readline(""));
}

void	init_redir_fd(t_shell *shell, t_redir *redir)
{
	t_tmpfile	*next;

	if (redir->type == e_append)
		redir->fd = open(redir->str,
				O_CREAT | O_APPEND | O_RDWR | O_CLOEXEC, 0644);
	if (redir->type == e_replace)
		redir->fd = open(redir->str,
				O_CREAT | O_TRUNC | O_RDWR | O_CLOEXEC, 0644);
	if (redir->type == e_in)
		redir->fd = open(redir->str, O_RDONLY | O_CLOEXEC);
	if (redir->type == e_until)
	{
		if (!shell->tmpfile_list)
			ft_printf_fd(2, "Tmpfile doesn't exist\n");
		redir->fd = open(shell->tmpfile_list->name, O_RDONLY | O_CLOEXEC);
		if (unlink(shell->tmpfile_list->name) == -1)
			perror("unlink");
		next = shell->tmpfile_list->next;
		free(shell->tmpfile_list->name);
		free(shell->tmpfile_list);
		shell->tmpfile_list = next;
	}
}

int	get_exit_status(t_cmd *cmd)
{
	if (WIFEXITED(cmd->status))
		return (WEXITSTATUS(cmd->status));
	else if (WIFSIGNALED(cmd->status))
		return (128 + WTERMSIG(cmd->status));
	return (1);
}
