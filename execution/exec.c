/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:22:45 by rrollin           #+#    #+#             */
/*   Updated: 2022/07/01 15:17:23 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	exec(t_cmd_element *cmd)
{
	int	res;

	res = !(!ft_strcmp((const char *) cmd->str, "echo"));
	printf("Execution de ");
	print_element(cmd);
	printf(", retour : %d\n", res);
	return (res);
}

int	is_single_cmd(t_cmd_element *cmd)
{
	while (cmd)
	{
		if (cmd->type != WORD && cmd->type != REDIRECT)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	ft_exec_bloc(t_cmd_element *input)
{
	if (got_parenthesis(input))
		remove_parenthesis(&input);
	if (is_single_cmd(input))
		return (exec(input));
	else
		return (ft_split_cmd(input));
}
