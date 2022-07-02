/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:05:07 by johrober          #+#    #+#             */
/*   Updated: 2022/07/02 16:45:43 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_wildcards(t_cmd_element **list)
{
	t_cmd_element	*current;
	t_cmd_element	*previous;
	t_cmd_element	*end;
	char			**matching_files;
	int				count;

	current = *list;
	previous = NULL;
	while (current)
	{
		if (current->type == WORD && ft_str_contains(current->str, '*'))
		{
			matching_files = get_matching_files(current->str);
			if (matching_files)
			{
				current->str = matching_files[0];
				count = 0;
				end = current->next;
				previous = current;
				while (matching_files[++count])
				{
					current = init_element(matching_files[count], WORD);
					previous->next = current;
					previous = current;
				}
				current->next = end;
				free(matching_files);
			}
		}
		current = current->next;
	}
}

char	**get_matching_files(char *expr)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			**matching_files;

	matching_files = NULL;
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent)
	{
		if (is_matching_wildcard(dirent->d_name, expr))
			ft_tab_insert((void ***)&matching_files,
					ft_tablen((const void **)matching_files),
					ft_strdup(dirent->d_name));
		dirent = readdir(dir);
	}
	closedir(dir);
	//if (!matching_files)
		//Output error (no match found)
	return (matching_files);
}

int	is_matching_wildcard(char *name, char *expr)
{
	char	*wildcard;
	char	*match;
	int		length;

	wildcard = ft_strchr(expr, '*');
	length = wildcard - expr;
	if (length > 0 && ft_strncmp(name, expr, length))
		return (0);
	expr += length + 1;
	name += length + 1;
	while (*expr && *expr == '*')
		expr++;
	if (!*expr)
		return (1);
	wildcard = ft_strchr(expr, '*');
	while (wildcard)
	{
		length = wildcard - expr;
		match = ft_strsubstr(name, expr, length);
		if (!match)
			return (0);
		name = match + length;
		expr += length + 1;
		while (*expr && *expr == '*')
			expr++;
		if (!*expr)
			return (1);
		wildcard = ft_strchr(expr, '*');
	}
	match = ft_strsubstr(name, expr, ft_strlen(expr));
	if (match && ft_strlen(match) == ft_strlen(expr))
		return (1);
	return (0);
}
