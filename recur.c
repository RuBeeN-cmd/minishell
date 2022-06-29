/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:22:45 by rrollin           #+#    #+#             */
/*   Updated: 2022/06/29 15:10:53 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_get_split_index(const char *str, const char *delimiter)
{
	int		i;
	int		j;
	size_t	str_len;
	size_t	delimiter_len;

	if (!delimiter || !str)
		return (-1);
	str_len = ft_strlen(str);
	delimiter_len = ft_strlen(delimiter);
	i = 0;
	while (i + delimiter_len <= str_len)
	{
		if (!delimiter[0])
			return (0);
		if (str[i] == delimiter[0])
		{
			j = 0;
			while (str[i + j] == delimiter[j] && str[i + j] && delimiter[j])
				j++;
			if (!delimiter[j])
				return (i);
		}
		i++;
	}
	return (-1);
}

int exec(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_exec_bloc(char *str)
{
	int		and_index;
	int		or_index;
	char	*cmd;
	char	*block;

	and_index = ft_get_split_index((const char *) str, "&&");
	or_index = ft_get_split_index((const char *) str, "||");
	if ((and_index < or_index && and_index != -1) || (and_index != -1 && or_index == -1)) // <---------- && found first
	{
		cmd = ft_substr(str, 0, and_index);
		block = ft_substr(str, and_index + 2, ft_strlen(str) - and_index - 2);
		if (exec(cmd))
			ft_exec_bloc(block);
	}
	else if ((or_index < and_index && or_index != -1) || (or_index != -1 && and_index == -1)) // <---------- || found first
	{
		cmd = ft_substr(str, 0, or_index);
		block = ft_substr(str, or_index + 2, ft_strlen(str) - or_index - 2);
		if (!exec(cmd))
			ft_exec_bloc(block);
	}
	else // <---------- nothing found
		exec(str);
}
