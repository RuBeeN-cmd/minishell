/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:04:22 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/11 18:28:13 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	got_parenthesis(t_cmd_element *input)
{
	return (input->type == e_par
		&& !ft_strcmp((const char *) input->str, "("));
}

void	remove_parenthesis(t_cmd_element **input)
{
	t_cmd_element	*tmp;
	t_cmd_element	*tmp_tmp;
	int				nb_parenthesis;

	tmp = (*input)->next;
	destroy_element(*input);
	*input = tmp;
	nb_parenthesis = 1;
	while (tmp->next)
	{
		if (tmp->next->type == e_par)
		{
			nb_parenthesis += 1 * !ft_strcmp((const char *) tmp->next->str, "(")
				+ -1 * !!ft_strcmp((const char *) tmp->next->str, "(");
		}
		if (!nb_parenthesis)
		{
			tmp_tmp = tmp->next;
			tmp->next = tmp_tmp->next;
			destroy_element(tmp_tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void	remove_pipe_parenthesis(t_cmd_element **input)
{
	t_cmd_element	*tmp;

	tmp = *input;
	while (*input)
	{
		if ((*input)->type == e_pipe)
			if (got_parenthesis((*input)->next))
				remove_parenthesis(&((*input)->next));
		*input = (*input)->next;
	}
	*input = tmp;
}
