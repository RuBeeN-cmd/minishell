/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:04:22 by rrollin           #+#    #+#             */
/*   Updated: 2022/07/01 15:35:00 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	got_parenthesis(t_cmd_element *input)
{
	int	nb_parenthesis;

	if (input->type == PARENTHESIS
		&& !ft_strcmp((const char *) input->str, "("))
	{
		nb_parenthesis = 1;
		input = input->next;
		while (input->next)
		{
			if (input->type == PARENTHESIS)
			{
				if (!ft_strcmp((const char *) input->str, "("))
					nb_parenthesis++;
				else
					nb_parenthesis--;
			}
			if (!nb_parenthesis)
				return (0);
			input = input->next;
		}
		return (input->type == PARENTHESIS
			&& !ft_strcmp((const char *) input->str, ")")
			&& nb_parenthesis == 1);
	}
	else
		return (0);
}

void	remove_parenthesis(t_cmd_element **input)
{
	t_cmd_element	*tmp;

	tmp = (*input)->next;
	destroy_element(*input);
	*input = tmp;
	while (tmp->next->next)
		tmp = tmp->next;
	destroy_element(tmp->next);
	tmp->next = NULL;
}
