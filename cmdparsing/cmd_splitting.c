/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_splitting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:16:52 by johrober          #+#    #+#             */
/*   Updated: 2022/08/06 11:46:10 by johrober         ###   ########.fr       */
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

/* t_cmd_element	*parse_word_element(t_shell *shell, char **str) */
/* { */
/* 	char			*str_parsed; */
/* 	char			*word_break; */
/* 	char			*quote_end; */

/* 	str_parsed = NULL; */
/* 	word_break = ft_strchr_any(*str, "\'\" \t><|&()"); */
/* 	while (word_break && ft_str_contains("\'\"", *word_break)) */
/* 	{ */
/* 		str_parsed = ft_strjoin_free(str_parsed, */
/* 				parse_substring(shell, *str, word_break - *str)); */
/* 		quote_end = ft_strchr(word_break + 1, *word_break); */
/* 		if (!quote_end) */
/* 			str_parsed = ft_stradd(str_parsed, *word_break); */
/* 		if (!quote_end) */
/* 			quote_end = word_break; */
/* 		else if (*word_break == '\'') */
/* 			str_parsed = ft_strnjoin(str_parsed, word_break + 1, quote_end - word_break - 1); */
/* 		else */
/* 			str_parsed = ft_strjoin_free(str_parsed, parse_substring(shell, word_break + 1, quote_end - word_break - 1)); */
/* 		*str = quote_end + 1; */
/* 		word_break = ft_strchr_any(*str, "\'\" \t><|&()"); */
/* 	} */
/* 	if (!word_break) */
/* 		word_break = ft_strchr(*str, 0); */
/* 	str_parsed = ft_strjoin_free(str_parsed, */
/* 			parse_substring(shell, *str, word_break - *str)); */
/* 	*str = word_break; */
/* 	return (init_element(str_parsed, WORD)); */
/* } */

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

/* int	**detect_wildcards(int **wildcards, char *str_parsed, char *to_add) */
/* { */
/* 	char	*wc; */
/* 	int		*wc_pos; */

/* 	wc = ft_strchr(to_add, '*'); */
/* 	while (wc) */
/* 	{ */
/* 		wc_pos = malloc(sizeof(int)); */
/* 		*wc_pos = ft_strlen(str_parsed) + wc - to_add; */
/* 		ft_tab_insert_last((void ***)&wildcards, wc_pos); */
/* 		wc = ft_strchr(wc + 1, '*'); */
/* 	} */
/* 	return (wildcards); */
/* } */

char	*parse_substring(t_shell *shell, char *str, int length)
{
	char	*str_parsed;
	char	*base_str;
	char	*var_str;

	str_parsed = NULL;
	base_str = str;
	var_str = ft_strchr(str, '$');
	while (var_str && var_str - base_str < length)
	{
		str_parsed = ft_strnjoin(str_parsed, str, var_str - str);
		str = var_str;
		str_parsed = ft_strjoin_free(str_parsed, parse_var_call(shell, &str));
		var_str = ft_strchr(str, '$');
	}
	str_parsed = ft_strnjoin(str_parsed, str, length - (str - base_str));
	return (str_parsed);
}

char	*parse_var_call(t_shell *shell, char **str)
{
	char		*str_var;
	char		*base_str;
	t_env_var	*var;

	*str = *str + 1;
	base_str = *str;
	if (ft_isdigit(**str) || **str == '?')
		*str = *str + 1;
	else
		while (**str && (ft_isalpha(**str) || ft_isdigit(**str) || **str == '_'))
			*str = *str + 1;
	if (*str == base_str)
		return (ft_strdup("$"));
	str_var = ft_substr(base_str, 0, *str - base_str);
	if (!ft_strcmp(str_var, "?"))
	{
		free(str_var);
		return (ft_itoa(shell->exit_status));
	}
	var = get_env_var(shell, str_var);
	free(str_var);
	if (var)
		return (ft_strdup(var->value));
	return (ft_strdup(""));
}
