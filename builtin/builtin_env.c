/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:24:46 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/09 14:31:25 by rrollin          ###   ########.fr       */
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
	int		exit_status;
	int		i;

	exit_status = EXIT_SUCCESS;
	i = 0;
	while (++i < argc)
	{
		if (is_valid_expr(argv[i]))
			crea_mod_env_var(shell, argv[i]);
		else
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier.\n", argv[i]);
			exit_status = EXIT_FAILURE;
		}
	}
	return (exit_fork(shell, exit_status));
}

int	unset(t_shell *shell, int argc, char **argv)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = EXIT_SUCCESS;
	while (++i < argc)
	{
		if (is_valid_identifier(argv[i]))
			remove_env_var(shell, argv[i]);
		else
		{
			ft_printf_fd(2, "unset: '%s': not a valid identifier.\n", argv[i]);
			exit_status = EXIT_FAILURE;
		}
	}
	if (argc == 1)
	{
		ft_printf_fd(2, "unset: not enough arguments.\n");
		return (exit_fork(shell, exit_status));
	}
	return (exit_fork(shell, exit_status));
}
