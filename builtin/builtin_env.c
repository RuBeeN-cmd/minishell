/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:24:46 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/04 17:19:49 by rrollin          ###   ########.fr       */
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
			var = get_var_export(argv[i]);
			if (is_valid_identifier(var[0]))
			{
				crea_mod_env_var(shell, var);
				return (exit_fork(shell, EXIT_SUCCESS));
			}
			ft_free_tab((void **) var);
			ft_printf_fd(2, "export: not a valid identifier\n");
			return (exit_fork(shell, EXIT_FAILURE));
		}
		else if (eq_ptr == argv[i])
		{
			ft_printf_fd(2, "export: invalids arguments\n");
			return (exit_fork(shell, EXIT_FAILURE));
		}
	}
	return (exit_fork(shell, EXIT_SUCCESS));
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
