/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_any.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:27:48 by johrober          #+#    #+#             */
/*   Updated: 2022/06/27 16:31:15 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_any(char *str, char *charset)
{
	while(*str)
	{
		if (ft_str_contains(charset, *str))
			return (str);
		str++;
	}
	if (ft_str_contains(charset, '\0'))
		return (str);
	return (NULL);
}
