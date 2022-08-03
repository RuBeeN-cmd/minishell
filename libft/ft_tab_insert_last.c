/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_insert_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:14:05 by johrober          #+#    #+#             */
/*   Updated: 2022/08/03 11:31:22 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tab_insert_last(void ***tab, void *to_insert)
{
	ft_tab_insert(tab, ft_tablen((const void **)*tab), to_insert);
}
