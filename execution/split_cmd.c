/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:05:15 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/10 19:51:58 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	ft_get_blocks(t_cmd_element *input, t_cmd_element **cmd,
	t_cmd_element **op, t_cmd_element **nxt_block)
{
	t_cmd_element	*tmp;
	int				is_in_parenthesis;

	is_in_parenthesis = 0;
	*cmd = input;
	if (input->type == PARENTHESIS)
		is_in_parenthesis++;
	while (input->next)
	{
		if (input->next->type == PARENTHESIS)
		{
			if (!ft_strcmp((const char *) input->next->str, "("))
				is_in_parenthesis++;
			else
				is_in_parenthesis--;
		}
		else if (input->next->type == OPERATOR && !is_in_parenthesis)
			tmp = input;
		input = input->next;
	}
	*op = tmp->next;
	tmp->next = NULL;
	*nxt_block = (*op)->next;
	(*op)->next = NULL;
}

int	ft_split_cmd(t_shell *shell, t_cmd_element *input, int ex)
{
	t_cmd_element	*op;
	t_cmd_element	*cmd;
	t_cmd_element	*nxt_block;
	int				ret;

	ft_get_blocks(input, &cmd, &op, &nxt_block);
	if (!ft_strcmp(op->str, "&&"))
	{
		destroy_element(op);
		ret = ft_exec_bloc(shell, cmd, ex);
		if (!ret)
			return (ft_exec_bloc(shell, nxt_block, (ex)));
		ft_exec_bloc(shell, nxt_block, 0);
		return (1);
	}
	else if (!ft_strcmp(op->str, "||"))
	{
		destroy_element(op);
		ret = ft_exec_bloc(shell, cmd, ex);
		if (ret)
			return (ft_exec_bloc(shell, nxt_block, ex));
		ft_exec_bloc(shell, nxt_block, 0);
		return (1);
	}
	return (0);
}
