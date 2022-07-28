/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:10:30 by johrober          #+#    #+#             */
/*   Updated: 2022/07/26 16:02:48 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	count;

	if (!*to_find)
		return (str);
	while (*str)
	{
		count = 0;
		while (str[count] == to_find[count] && to_find[count])
			count++;
		if (!to_find[count])
			return (str);
		str++;
	}
	return (NULL);
}
