/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:21:53 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 18:17:06 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tab_remove(void ***tab, void *to_remove)
{
	void	**new;
	int		length;
	int		count;

	if (!to_remove || !tab || !(*tab) || !ft_tab_contains(tab, to_remove))
		return ;
	length = ft_tablen((const void **)*tab);
	new = malloc(sizeof(void *) * length);
	new[length - 1] = NULL;
	count = -1;
	while ((*tab)[++count] && (*tab)[count] != to_remove)
		new[count] = (*tab)[count];
	while ((*tab)[count] && (*tab)[++count])
		new[count - 1] = (*tab)[count];
	free(*tab);
	if (length == 1)
		free(new);
	if (length == 1)
		new = NULL;
	*tab = new;
}	
