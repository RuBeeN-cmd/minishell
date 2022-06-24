/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:24:46 by rrollin           #+#    #+#             */
/*   Updated: 2022/06/22 16:24:59 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_export(t_shell *shell, char **cmd)
{
	t_env_var	*env_var_ptr;
	char		**var;
	char		*eq_ptr;

	if (!cmd)
		return ;
	while (*(++cmd))
	{
		eq_ptr = ft_strchr(*cmd, '=');
		if (eq_ptr && eq_ptr != *cmd)
		{
			var = ft_split(*cmd, '=');
			env_var_ptr = get_env_var(shell, var[0]);
			if (env_var_ptr)
				env_var_ptr->value = var[1];
			else
				add_env_var(shell, var[0], var[1]);
			free(var);
		}
	}
}