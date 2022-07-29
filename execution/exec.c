/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:22:45 by rrollin           #+#    #+#             */
/*   Updated: 2022/07/28 14:39:20 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	exec(t_shell *shell, t_cmd_element *list)
{
	int		status;
	pid_t	last_child_pid;

	shell->cmd_tab = parse_final(list);
	if (ft_tablen((const void **)shell->cmd_tab) == 1)
	{
		shell->exit_status = call_builtin_if_exists(shell, shell->cmd_tab[0]);
		if (shell->exit_status == -1)
		{
			last_child_pid = execute(shell, shell->cmd_tab);
			waitpid(last_child_pid, &status, 0);
			shell->exit_status = WEXITSTATUS(status);
		}
	}
	else
	{
		last_child_pid = execute(shell, shell->cmd_tab);
		waitpid(last_child_pid, &status, 0);
		shell->exit_status = WEXITSTATUS(status);
	}
	ft_destroy_tab((void ***)&shell->cmd_tab, (void (*)(void *))destroy_cmd);
	shell->cmd_tab = NULL;
	if (shell->exit_status == EXIT_SUCCESS)
		return (0);
	return (1);
}

int	is_single_cmd(t_cmd_element *cmd)
{
	while (cmd)
	{
		if (cmd->type == OPERATOR)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	ft_exec_bloc(t_shell *shell, t_cmd_element *input)
{
	if (got_parenthesis(input))
		remove_parenthesis(&input);
	remove_pipe_parenthesis(&input);
	if (is_single_cmd(input))
		return (exec(shell, input));
	else
		return (ft_split_cmd(shell, input));
}
