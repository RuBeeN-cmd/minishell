/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_splitting_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:51:53 by johrober          #+#    #+#             */
/*   Updated: 2022/08/03 12:48:46 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		to_add = ft_stradd(to_add, **str);
	if (!quote_end)
		quote_end = *str;
	else if (**str == '\'')
		to_add = ft_substr(*str, 1, quote_end - *str - 1);
	else
		to_add = parse_substring(shell, *str + 1, quote_end - *str - 1);
	*str = quote_end + 1;
	return (to_add);
}

