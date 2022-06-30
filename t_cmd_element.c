/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:32:11 by johrober          #+#    #+#             */
/*   Updated: 2022/06/30 15:50:03 by johrober         ###   ########.fr       */
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
