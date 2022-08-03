/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tab_alpha.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:49:19 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/03 15:35:59 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_strcmp_caseless(const char *s1, const char *s2)
{
	int	count;

	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	count = 0;
	while (s1[count] && s2[count]
		&& ft_tolower(s1[count]) == ft_tolower(s2[count]))
		count++;
	return (ft_tolower(s1[count]) - ft_tolower(s2[count]));
}

static int	get_index_first_str(char **str)
{
	int	first_index;
	int	i;

	i = 1;
	first_index = 0;
	while (str[i])
	{
		if (ft_strcmp_caseless(str[i], str[first_index]) < 0)
			first_index = i;
		i++;
	}
	return (first_index);
}

static void	swap(char **str, int i, int j)
{
	char	*tmp;

	tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
}

void	ft_sort_tab_alpha(char **str)
{
	int	first_index;

	if (!(str && str[0]))
		return ;
	first_index = get_index_first_str(str);
	swap(str, 0, first_index);
	ft_sort_tab_alpha(str + 1);
}
