/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:05:07 by johrober          #+#    #+#             */
/*   Updated: 2022/08/03 12:49:31 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_element	*build_new_elements(char *str, int *wc_pos)
{
	int		count;
	char	**wc;
	char	**matching_files;

	if (!wc_pos)
		return (init_element(str, WORD));
	wc = malloc(sizeof(char *) * (ft_tablen((const void **)wc_pos + 1)));
	count = -1;
	while (wc_pos[++count] != -1)
		wc[count] = str + wc_pos[count];
	wc[count] = NULL;
	free(wc_pos);
	matching_files = get_matching_files(str, wc);
	free(wc);
	if (!matching_files)
		return (NULL);
	return (build_elements_from_matches(matching_files));
}

t_cmd_element	*build_elements_from_matches(char **matching_files)
{
	t_cmd_element	*previous;
	t_cmd_element	*current;
	t_cmd_element	*first;
	int				count;

	count = -1;
	current = NULL;
	previous = NULL;
	first = NULL;
	while (matching_files[++count])
	{
		current = init_element(matching_files[count], WORD);
		if (previous)
			previous->next = current;
		previous = current;
		if (!first)
			first = current;
	}
	free(matching_files);
	return (first);
}

char	**get_matching_files(char *expr, char **wildcards)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			**matching_files;

	matching_files = NULL;
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent)
	{
		if (is_matching_wildcard(dirent->d_name, expr, wildcards))
			ft_tab_insert((void ***)&matching_files,
				ft_tablen((const void **)matching_files),
				ft_strdup(dirent->d_name));
		dirent = readdir(dir);
	}
	closedir(dir);
	return (matching_files);
}

int	is_matching_wildcard(char *name, char *expr, char **wildcards)
{
	char	*wildcard;
	char	*match;
	int		length;

	wildcard = *(wildcards++);
	length = wildcard - expr;
	if (length > 0 && ft_strncmp(name, expr, length))
		return (0);
	if (advance_in_word(&name, &expr, length, name))
		return (1);
	wildcard = *(wildcards++);
	while (wildcard)
	{
		length = wildcard - expr;
		match = ft_strsubstr(name, expr, length);
		if (!match)
			return (0);
		if (advance_in_word(&name, &expr, length, match))
			return (1);
		wildcard = *(wildcards++);
	}
	match = ft_strsubstr(name, expr, ft_strlen(expr));
	if (match && ft_strlen(match) == ft_strlen(expr))
		return (1);
	return (0);
}

int	advance_in_word(char **name, char **expr, int length, char *match)
{
	*expr += length + 1;
	if (!**expr)
		return (1);
	*name = match + length;
	return (0);
}
