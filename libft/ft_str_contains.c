/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_contains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:02 by johrober          #+#    #+#             */
/*   Updated: 2022/06/21 12:48:53 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_contains(const char *str, char c)
{
	int	count;

	count = -1;
	while(str[++count])
	{
		if (str[count] == c)
			return (1);
	}
	return (0);
}
