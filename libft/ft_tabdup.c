/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:30:27 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 18:03:39 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_tabdup(void **tab)
{
	void	**new;
	int		i;

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
