/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:02:52 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 12:14:42 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_syntax_valid(t_cmd_element *list)
{
	t_cmd_element	*cur;
	int				words;

	cur = list;
	words = 0;
	while (cur)
	{
		if (cur->type == WORD)
			words++;
		if (cur->type == REDIRECT && (!cur->next || cur->next->type != WORD))
			return (0);
		if ((cur->type == OPERATOR || cur->type == PIPE) && !words)
			return (0);
		if (cur->type == OPERATOR || cur->type == PIPE)
			words = 0;
		cur = cur->next;
	}
	if (words == 0 || !is_parenthesis_syntax_valid(list))
	{
		if (list)
			ft_printf_fd(2, "Syntax error in command.\n");
		return (0);
	}
	return (1);
}

static void	add_word_to_parenthesis(int	*words, int parenthesis)
{
	int	count;

	count = parenthesis;
	while (count >= 0)
		words[count--] += 1;
}

static void	init_words(int *words)
{
	int	count;

	count = -1;
	while (++count < PARENTHESIS_NB)
		words[count] = -1;
}

static	int	are_parenthesis_in_between_operators(t_cmd_element *list)
{
	t_cmd_element	*cur;
	t_cmd_element	*prev;

	prev = NULL;
	cur = list;
	while (cur)
	{
		if (cur->type == PARENTHESIS)
		{
			if (!ft_strcmp(cur->str, "(") && prev && prev->type != OPERATOR
				&& (prev->type != PARENTHESIS
					|| !!ft_strcmp(prev->str, "(")))
				return (0);
			else if (!ft_strcmp(cur->str, ")") && cur->next &&
					cur->next->type != OPERATOR &&
					(cur->next->type != PARENTHESIS 
						|| !!ft_strcmp(cur->next->str, ")")))
				return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

int	is_parenthesis_syntax_valid(t_cmd_element *list)
{
	t_cmd_element	*cur;
	int				words[PARENTHESIS_NB];
	int				par;

	init_words((int *)words);
	par = -1;
	cur = list;
	while (cur)
	{
		if (cur->type == PARENTHESIS && !ft_strcmp(cur->str, "(") && par >= -1)
			words[++par] = 0;
		if (cur->type == WORD && cur->next && cur->next->type == PARENTHESIS
			&& !ft_strcmp(cur->next->str, "("))
			return (0);
		if (cur->type == WORD && par > -1)
			add_word_to_parenthesis((int *)words, par);
		if (cur->type == PARENTHESIS && !ft_strcmp(cur->str, ")")
			&& (par < 0 || words[par] == 0))
			return (0);
		if (cur->type == PARENTHESIS && !ft_strcmp(cur->str, ")"))
			words[par--] = -1;
		cur = cur->next;
	}
	return (par == -1 && are_parenthesis_in_between_operators(list));
}

