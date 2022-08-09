/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:44:16 by johrober          #+#    #+#             */
/*   Updated: 2022/08/09 14:58:14 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabsort(void **tab, int (*cmp)(void *, void *))
{
	int 	i;
	int		sorted;
	void	*buffer;

	sorted = 0;
	while (sorted != 1)
	{
		sorted = 1;
		i = 0;
		while (sorted && tab[i] && tab[i + 1])
		{
			if (cmp(tab[i], tab[i + 1]))
			{
				buffer = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = buffer;
				sorted = 0;
			}
			i++;
		}
	}
}
