/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:32:11 by johrober          #+#    #+#             */
/*   Updated: 2022/06/30 16:41:33 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_element	*init_element(char *str, t_elem_type type)
{
	t_cmd_element	*new;

	new = malloc(sizeof(t_cmd_element));
	new->next = NULL;
	new->str = str;
	new->type = type;
	return (new);
}

void	destroy_element(t_cmd_element *elem)
{
	free(elem->str);
	free(elem);
}

void	print_element(t_cmd_element *input)
{
	while (input)
	{
		printf("%s", input->str);
		input = input->next;
		if (input)
			printf(" ");
	}
}
