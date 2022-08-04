/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:22:45 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/04 13:17:55 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	exec(t_shell *shell, t_cmd_element *list)
{
	int count;
	int	nb_cmd;

	shell->cmd_tab = parse_final(list);
	nb_cmd = ft_tablen((const void **)shell->cmd_tab);
	if (nb_cmd == 1)
		shell->exit_status = call_builtin_if_exists(shell, shell->cmd_tab[0]);
	if (nb_cmd > 1 || shell->exit_status == -1)
	{	
		execute(shell);
		count = -1;
		while (shell->cmd_tab[++count])
			waitpid(shell->cmd_tab[count]->pid, &shell->cmd_tab[count]->status, 0);
		if (WIFEXITED(shell->cmd_tab[count - 1]->status))
			shell->exit_status = WEXITSTATUS(shell->cmd_tab[count - 1]->status);
		else if (WIFSIGNALED(shell->cmd_tab[count - 1]->status))
			shell->exit_status = 128 + WTERMSIG(shell->cmd_tab[count - 1]->status);
	}
	set_signal_handlers();
	if (shell->exit_status == 131)
		ft_printf_fd(2, "Quit (core dumped)\n");
	ft_destroy_tab((void ***)&shell->cmd_tab, (void (*)(void *))destroy_cmd);
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
