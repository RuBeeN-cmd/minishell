/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:32:11 by johrober          #+#    #+#             */
/*   Updated: 2022/08/05 10:57:21 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	destroy_element_list(t_cmd_element *elem)
{
	t_cmd_element	*current;
	t_cmd_element	*next;

	current = elem;
	while (current)
	{
		next = current->next;
		destroy_element(current);
		current = next;
	}
}

t_cmd_element	*detach_element(t_cmd_element **list, t_cmd_element *elem)
{
	t_cmd_element	*current;
	t_cmd_element	*previous;
	t_cmd_element	*to_return;

	current = *list;
	previous = NULL;
	while (current)
	{
		if (current == elem)
		{
			if (!previous)
				*list = current->next;
			else
				previous->next = NULL;
			to_return = current->next;
			destroy_element(elem);
			return (to_return);
		}
		previous = current;
		current = current->next;
	}
	return (NULL);
}

void	print_element(t_cmd_element *elem)
{
	printf("\tType :\t\t");
	if (elem->type == WORD)
		printf("Word\n");
	else if (elem->type == REDIRECT)
		printf("Redirect\n");
	else if (elem->type == OPERATOR)
		printf("Binary operator\n");
	else if (elem->type == PIPE)
		printf("Pipe\n");
	else if (elem->type == PARENTHESIS)
		printf("Parenthesis\n");
	else
		printf("Unknown");
	printf("\tContent\t\t%s\n", elem->str);
}
