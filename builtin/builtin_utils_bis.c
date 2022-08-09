/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:05:08 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/09 15:40:47 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	export_without_args(t_shell *shell)
{
	char		**env;
	t_env_var	*cur;
	int			i;

	i = 0;
	while (shell->env[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	env[i] = NULL;
	i = -1;
	while (shell->env[++i])
	{
		cur = shell->env[i];
		env[i] = ft_strdup(cur->name);
		env[i] = ft_strnjoin(env[i], "=\"", 2);
		env[i] = ft_strnjoin(env[i], cur->value, ft_strlen(cur->value));
		env[i] = ft_strnjoin(env[i], "\"", 1);
	}
	ft_sort_tab_alpha(env);
	i = -1;
	while (env[++i])
		ft_printf("declare -x %s\n", env[i]);
	ft_destroy_tab((void ***)&env, free);
}

void	exit_non_num_arg(t_shell *shell)
{
	ft_printf_fd(2, "exit: numeric argument required\n");
	destroy_tshell(shell);
	exit(2);
}

int	is_valid_identifier(char *name, int is_export)
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
			if (is_export)
				return (!name[i] || name[i] == '=');
			else
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
	char	*eq_ptr;

	eq_ptr = ft_strchr(str, '=');
	var = malloc(sizeof(char *) * 3);
	if (eq_ptr)
	{
		var[0] = ft_substr(str, 0, eq_ptr - str);
		var[1] = ft_substr(str, eq_ptr - str + 1, ft_strlen(str));
	}
	else
	{
		var[0] = ft_strdup(str);
		var[1] = NULL;
	}
	var[2] = NULL;
	return (var);
}


