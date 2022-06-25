/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:49:55 by johrober          #+#    #+#             */
/*   Updated: 2022/06/25 14:04:05 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tab_insert(void ***tab, int position, void *to_insert)
{
	void	**copy;
	int		length;
	int		count;
	
	length = ft_tablen((const void **)*tab);
	if (position > length)
		position = length;
	else if (position < 0)
		position = 0;
	copy = malloc(sizeof(void *) * (length + 2));
	copy[length + 1] = NULL;
	copy[position] = to_insert;
	count = -1;
	while ((*tab)[++count])
	{
		if (count >= position)
			copy[count + 1] = (*tab)[count];
		else if (count < position)
			copy[count] = (*tab)[count];
	}
	free(*tab);
	*tab = copy;
}
