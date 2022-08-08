/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:58:14 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/05 11:10:02 by rrollin          ###   ########.fr       */
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

void	init_redir_fd(t_redir *redir)
{
	if (redir->type == APPEND)
		redir->fd = open(redir->str,
				O_CREAT | O_APPEND | O_RDWR | O_CLOEXEC, 0644);
	if (redir->type == REPLACE)
		redir->fd = open(redir->str,
				O_CREAT | O_TRUNC | O_RDWR | O_CLOEXEC, 0644);
	if (redir->type == IN)
		redir->fd = open(redir->str, O_RDONLY | O_CLOEXEC);
}

void	set_exit_status(t_shell *shell, int count)
{
	if (WIFEXITED(shell->cmd_tab[count - 1]->status))
		shell->exit_status = WEXITSTATUS(shell->cmd_tab[count - 1]->status);
	else if (WIFSIGNALED(shell->cmd_tab[count - 1]->status))
		shell->exit_status = 128
			+ WTERMSIG(shell->cmd_tab[count - 1]->status);
}
