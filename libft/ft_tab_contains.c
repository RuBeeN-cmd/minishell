/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_contains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:17:20 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/11 18:17:31 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_tab_contains(void ***tab, void *elem)
{
	int	count;

	count = -1;
	while ((*tab)[++count])
		if (elem == (*tab)[count])
			return (1);
	return (0);
}
