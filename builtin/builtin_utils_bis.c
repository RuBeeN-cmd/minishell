/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:05:08 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/08 12:15:38 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	exit_non_num_arg(t_shell *shell)
{
	ft_printf_fd(2, "exit: numeric argument required\n");
	destroy_tshell(shell);
	exit(2);
}

int	is_valid_identifier(char *name)
{
	int	i;

	if (name)
	{
		i = 0;
		if ((name[0] >= 'A' && name[0] <= 'Z')
			|| (name[0] >= 'a' && name[0] <= 'z') || name[0] == '_')
		{
			while ((name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_')
				i++;
			return (!name[i]);
		}
	}
	return (0);
}

int	exit_fork(t_shell *shell, int exit_status)
{
	if (shell->fork)
	{
		destroy_tshell(shell);
		exit(exit_status);
	}
	return (exit_status);
}

char	**get_var_export(char *str)
{
	char		**var;

	var = ft_split(str, '=');
	if (!var[1])
		var[1] = ft_strdup("");
	return (var);
}
