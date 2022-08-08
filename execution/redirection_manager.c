/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:11:50 by johrober          #+#    #+#             */
/*   Updated: 2022/08/06 14:51:45 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_redirections(t_cmd *cmd)
{
	int		count;
	t_redir	*redir;
	t_redir	*last_until;

	last_until = NULL;
	count = -1;
	while (cmd->redir_tab && cmd->redir_tab[++count])
	{
		redir = cmd->redir_tab[count];
		if (redir->type == APPEND)
			redir->fd = open(redir->str, O_CREAT | O_APPEND | O_RDWR | O_CLOEXEC, 0644);
		if (redir->type == REPLACE)
			redir->fd = open(redir->str, O_CREAT | O_TRUNC | O_RDWR | O_CLOEXEC, 0644);
		if (redir->type == IN)
			redir->fd = open(redir->str, O_RDONLY | O_CLOEXEC);
		if (redir->type == UNTIL)
			last_until = redir;
		if (redir->fd == -1)
			perror(redir->str);
		if (redir->fd == -1)
			return (1);
	}
	if (last_until)
		return (handle_until_redirection(cmd, last_until));
	return (0);
}

void	set_redirections(t_shell *shell, t_cmd *cmd)
{
	int		count;
	t_redir	*redir;
	t_redir	*last_in;
	t_redir	*last_out;

	last_in = NULL;
	last_out = NULL;
	count = -1;
	while (cmd->redir_tab && cmd->redir_tab[++count])
	{
		redir = cmd->redir_tab[count];
		if (redir->type == APPEND || redir->type == REPLACE)
			last_out = redir;
		else if (redir->type == IN || redir->type == UNTIL)
			last_in = redir;
	}
	if (last_out)
		shell->stdout_dup = dup(1);
	if (last_out)
		dup2(last_out->fd, 1);
	if (last_in)
		shell->stdin_dup = dup(0);
	if (last_in)
		dup2(last_in->fd, 0);
}

void	close_redirections(t_shell *shell, t_cmd *cmd)
{
	int		count;
	t_redir	*redir;
	
	if (shell->stdin_dup != -1)
	{
		dup2(shell->stdin_dup, 0);
		close(shell->stdin_dup);
		shell->stdin_dup = -1;
	}
	if (shell->stdout_dup != -1)
	{
		dup2(shell->stdout_dup, 1);
		close(shell->stdout_dup);
		shell->stdout_dup = -1;
	}
	count = -1;
	while (cmd->redir_tab && cmd->redir_tab[++count])
	{
		redir = cmd->redir_tab[count];
		if (redir->fd != -1)
			close(redir->fd);
		if (redir->fd != -1)
			redir->fd = -1;
	}
}

char	*find_unused_filename(void)
{
	char	*filename;
	int		index;

	filename = ft_strdup(".tmp0000000");
	while (!access(filename, F_OK) || errno != ENOENT)
	{
		index = 10;
		while (filename[index] == '9' && index > 3)
			filename[index--] = '0';
		if (index <= 3)
			break;
		filename[index] += 1;
	}
	if (access(filename, F_OK) != 0)
		return (filename);
	free(filename);
	ft_printf_fd(2, "Unused filename for tmpfile not found");
	return (NULL);
}

void	remove_signal_handlers_for_redir()
{
	signal(SIGINT, SIG_DFL);
}

int	handle_until_redirection(t_cmd *cmd, t_redir *last_until)
{
	char	*line;
	pid_t	pid;

	cmd->tmpfile_name = find_unused_filename();
	if (!cmd->tmpfile_name)
		return (1);
	last_until->fd = open(cmd->tmpfile_name, O_CREAT | O_RDWR | O_EXCL, 0777);
	if (last_until->fd == -1)
		perror("open:");
	if (last_until->fd == -1)
		return (1);
	/* remove_signal_handlers(); */
	remove_signal_handlers_for_redir();
	pid = fork();
	if (!pid)
	{
		line = readline("");
		while (line && ft_strcmp(line, last_until->str) != 0)
		{
			ft_printf_fd(last_until->fd, line);
			ft_printf_fd(last_until->fd, "\n");
			free(line);
			line = readline("");
		}
		if (!line)
			ft_printf_fd(2, "warning : here-document delimited by EOF (wanted '%s')\n", last_until->str);
		if (line)
			free(line);
		close(last_until->fd);
		destroy_cmd(cmd);
	}
	set_signal_handlers();
	waitpid(pid, &cmd->status, 0);
	if (!WIFEXITED(cmd->status && WIFSIGNALED(cmd->status) && WTERMSIG(cmd->status) == 2))
		cmd->interrupt = 1;
	close(last_until->fd);
	last_until->fd = open(cmd->tmpfile_name, O_RDONLY | O_CLOEXEC);
	return (0);
}
