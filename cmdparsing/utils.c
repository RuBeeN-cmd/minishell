/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:53:57 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/11 18:31:34 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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
	if (**str && (ft_isdigit(**str) || **str == '?'))
		*str = *str + 1;
	else
		while (**str && (ft_isalnum(**str) || **str == '_'))
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

void	print_element_list(t_cmd_element *elem)
{
	t_cmd_element	*current;
	int				count;

	current = elem;
	count = 1;
	while (current)
	{
		printf("Element %2.d\n", count);
		print_element(current);
		count++;
		current = current->next;
	}
}

void	detatch_pipe(t_cmd_element **current, t_cmd_element **list_start,
	t_cmd ***tab, int *count)
{
	if ((*current)->type == e_pipe)
	{
		*current = detach_element(list_start, *current);
		ft_tab_insert((void ***)tab, (*count)++,
			parse_single_cmd(*list_start));
		destroy_element_list(*list_start);
		*list_start = *current;
	}
}
