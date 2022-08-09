/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:05:08 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/09 14:58:21 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	exit_non_num_arg(t_shell *shell)
{
	ft_printf_fd(2, "exit: numeric argument required\n");
	destroy_tshell(shell);
	exit(2);
}

int	is_valid_expr(char *expr)
{
	int	i;

	if (expr)
	{
		i = 0;
		if ((expr[0] >= 'A' && expr[0] <= 'Z')
			|| (expr[0] >= 'a' && expr[0] <= 'z') || expr[0] == '_')
		{
			while ((expr[i] >= 'A' && expr[i] <= 'Z')
				|| (expr[i] >= 'a' && expr[i] <= 'z')
				|| (expr[i] >= '0' && expr[i] <= '9')
				|| expr[i] == '_')
				i++;
			return (!expr[i] || expr[i] == '=');
		}
	}
	return (0);
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
	char	**var;
	char	**var_tmp;

	var_tmp = ft_split(str, '=');
	var = malloc(sizeof(char *) * 3);
	var[0] = var_tmp[0];
	var[1] = var_tmp[1];
	var[2] = NULL;
	free(var_tmp);
	return (var);
}
