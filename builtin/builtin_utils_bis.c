/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:05:08 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/09 14:57:18 by johrober         ###   ########.fr       */
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
		env[i] = ft_strnjoin(env[i], "=", 1);
		env[i] = ft_strnjoin(env[i], cur->value, ft_strlen(cur->value));
	}
	ft_sort_tab_alpha(env);
	i = -1;
	while (env[++i])
		ft_printf("declare -x \"%s\"\n", env[i]);
}

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


