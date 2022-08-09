/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:30:27 by johrober          #+#    #+#             */
/*   Updated: 2022/08/09 14:57:55 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_tabdup(void **tab)
{
	void	**new;
	int i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(void *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		new[i] = tab[i];
	new[i] = NULL;
	return (new);
}
