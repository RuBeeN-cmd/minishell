/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:31:29 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 10:32:17 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_tshell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->prompt = "\e[1;34m>\033[0;37m ";
	tcgetattr(0, &shell->termios_shell);
	shell->termios_shell.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &shell->termios_shell);
	shell->env = init_env(env);
	shell->pwd = NULL;
	shell->fork = 0;
	shell->pwd = getcwd(shell->pwd, 0);
	shell->cmd_tab = NULL;
	shell->stdin_dup = -1;
	shell->stdout_dup = -1;
	shell->interrupt = 0;
	shell->elem_left = NULL;
	shell->exit_status = 0;
	shell->tmpfile_list = NULL;
	init_builtin_list(shell);
	return (shell);
}

void	destroy_tshell(t_shell *shell)
{
	destroy_env(shell->env);
	destroy_builtin_list(shell);
	shell->env = NULL;
	if (shell->pwd)
		free(shell->pwd);
	if (shell->cmd_tab)
		ft_destroy_tab((void ***)&shell->cmd_tab,
			(void (*)(void *))destroy_cmd);
	if (shell->tmpfile_list)
		destroy_tmpfile_list(shell);
	if (shell->elem_left)
		ft_destroy_tab((void ***)&shell->elem_left,
			(void (*)(void *))destroy_element_list);
	free(shell);
}

void	destroy_tmpfile_list(t_shell *shell)
{
	t_tmpfile	*current;
	t_tmpfile	*next;

	current = shell->tmpfile_list;
	while (current)
	{
		next = current->next;
		if (!shell->fork)
			if (unlink(current->name) == -1)
				perror("unlink");
		free(current->name);
		free(current);
		current = next;
	}
}
