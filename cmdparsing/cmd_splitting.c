/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_splitting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:16:52 by johrober          #+#    #+#             */
/*   Updated: 2022/08/08 12:57:42 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_element	*split_into_element_list(t_shell *shell, char *str)
{
	t_cmd_element	*first;
	t_cmd_element	*current;
	t_cmd_element	*last;

	first = NULL;
	current = NULL;
	while (*str)
	{
		if (!ft_str_contains(" \t", *str))
		{
			current = parse_element_at(shell, &str);
			if (first == NULL)
				first = current;
			else
				last->next = current;
			while (current != NULL)
			{
				last = current;
				current = current->next;
			}
		}
		else
			str++;
	}
	return (first);
}

t_cmd_element	*parse_element_at(t_shell *shell, char **str)
{
	t_elem_type	type;
	int			length;

	if (ft_str_contains("><", **str))
		type = REDIRECT;
	else if (ft_str_contains("&|", **str) && (*str)[0] == (*str)[1])
		type = OPERATOR;
	else if (ft_str_contains("()", **str))
		type = PARENTHESIS;
	else if (**str == '|')
		type = PIPE;
	else
		type = WORD;
	if (type == PIPE || type == PARENTHESIS
		|| (type == REDIRECT && (*str)[0] != (*str)[1]))
		length = 1;
	else if (type != WORD)
		length = 2;
	else
		return (parse_word_element(shell, str));
	*str += length;
	return (init_element(ft_substr(*str - length, 0, length), type));
}

t_cmd_element	*parse_word_element(t_shell *shell, char **str)
{
	char	*str_parsed;
	char	*word_break;
	char	*to_add;
	int		*wildcards;

	str_parsed = NULL;
	wildcards = NULL;
	word_break = ft_strchr_any(*str, "\'\" \t><|&()");
	while (word_break && ft_str_contains("\'\"", *word_break))
	{
		to_add = parse_substring(shell, *str, word_break - *str);
		wildcards = detect_wildcards(wildcards, str_parsed, to_add);
		str_parsed = ft_strjoin_free(str_parsed, to_add);
		*str = word_break;
		to_add = parse_quote(shell, str);
		str_parsed = ft_strjoin_free(str_parsed, to_add);
		word_break = ft_strchr_any(*str, "\'\" \t><|&()");
	}
	if (!word_break)
		word_break = ft_strchr(*str, 0);
	to_add = parse_substring(shell, *str, word_break - *str);
	wildcards = detect_wildcards(wildcards, str_parsed, to_add);
	str_parsed = ft_strjoin_free(str_parsed, to_add);
	*str = word_break;
	return (build_new_elements(str_parsed, wildcards));
}

char	*parse_quote(t_shell *shell, char **str)
{
	char	*quote_end;
	char	*to_add;

	to_add = NULL;
	quote_end = ft_strchr(*str + 1, **str);
	if (!quote_end)
		to_add = ft_strnjoin(to_add, *str, 1);
	if (!quote_end)
		quote_end = *str;
	else if (**str == '\'')
		to_add = ft_substr(*str, 1, quote_end - *str - 1);
	else
		to_add = parse_substring(shell, *str + 1, quote_end - *str - 1);
	*str = quote_end + 1;
	return (to_add);
}

int	*detect_wildcards(int *wildcards, char *str_parsed, char *to_add)
{
	char	*wc;
	int		count;
	int		*new_wc;

	count = 0;
	while (wildcards && wildcards[count] != -1)
		count++;
	wc = ft_strchr(to_add, '*');
	while (wc)
	{
		wc = ft_strchr(wc + 1, '*');
		count++;
	}
	new_wc = malloc(sizeof(int) * (count + 1));
	count = -1;
	while (++count != -1 && wildcards && wildcards[count] != -1)
		new_wc[count] = wildcards[count];
	wc = ft_strchr(to_add, '*');
	while (wc)
	{
		new_wc[count++] = ft_strlen(str_parsed) + wc - to_add;
		wc = ft_strchr(wc + 1, '*');
	}
	new_wc[count] = -1;
	if (wildcards)
		free(wildcards);
	return (new_wc);
}
