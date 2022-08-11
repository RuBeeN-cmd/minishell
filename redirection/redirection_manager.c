/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:11:50 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 18:03:37 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_redirections(t_shell *shell, t_cmd *cmd)
{
	int		count;
	t_redir	*redir;

	count = -1;
	while (cmd->redir_tab && cmd->redir_tab[++count])
	{
		redir = cmd->redir_tab[count];
		init_redir_fd(shell, redir);
		if (redir->fd == -1)
			perror(redir->str);
		if (redir->fd == -1)
			return (1);
	}
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

	if (shell->stdin_dup != -1 && shell->stdin_dup != -2)
	{
		dup2(shell->stdin_dup, 0);
		close(shell->stdin_dup);
		shell->stdin_dup = -1;
	}
	if (shell->stdout_dup != -1 && shell->stdout_dup != -2)
	{
		dup2(shell->stdout_dup, 1);
		close(shell->stdout_dup);
		shell->stdout_dup = -1;
	}
	count = -1;
	while (cmd->redir_tab && cmd->redir_tab[++count])
	{
		redir = cmd->redir_tab[count];
		if (redir->fd != -1 && redir->fd != -2)
			close(redir->fd);
		if (redir->fd != -1 && redir->fd != -2)
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
			break ;
		filename[index] += 1;
	}
	if (access(filename, F_OK) != 0)
		return (filename);
	free(filename);
	ft_printf_fd(2, "Unused filename for tmpfile not found");
	return (NULL);
}
