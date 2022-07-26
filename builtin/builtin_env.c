/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:24:46 by rrollin           #+#    #+#             */
/*   Updated: 2022/07/26 16:36:56 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	env(t_shell *shell, int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		print_env(shell);
		return (EXIT_SUCCESS);
	}
	else
		ft_printf_fd(2, "env: too many arguments\n");
	return (EXIT_FAILURE);
}

void	crea_mod_env_var(t_shell *shell, char **var)
{
	t_env_var	*env_var_ptr;

	env_var_ptr = get_env_var(shell, var[0]);
	if (env_var_ptr)
		env_var_ptr->value = var[1];
	else
		add_env_var(shell, var[0], var[1]);
}

int	export(t_shell *shell, int argc, char **argv)
{
	char		**var;
	char		*eq_ptr;
	int			i;

	i = 0;
	while (++i < argc)
	{
		eq_ptr = ft_strchr(argv[i], '=');
		if (eq_ptr && eq_ptr != argv[i])
		{
			var = ft_split(argv[i], '=');
			if (!var[1])
				var[1] = ft_strdup("");
			crea_mod_env_var(shell, var);
			free(var);
			if (shell->fork)
				exit(EXIT_SUCCESS);
		}
		else if (eq_ptr == argv[i])
		{
			ft_printf_fd(2, "export: invalids arguments\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	unset(t_shell *shell, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		remove_env_var(shell, argv[i]);
	if (argc == 1)
	{
		ft_printf_fd(2, "unset: not enough arguments.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
