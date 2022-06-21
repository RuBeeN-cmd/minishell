/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:16:52 by johrober          #+#    #+#             */
/*   Updated: 2022/06/21 12:54:22 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(t_shell *shell, char *str)
{
	char	**tab_str;
	char	*command;
	char	*path;
	
	tab_str = ft_split(str);
	command = tab_str[0];
	if (!ft_str_contains("./~", command[0]))
	{

	}
}
