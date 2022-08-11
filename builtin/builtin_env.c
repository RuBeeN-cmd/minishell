/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:24:46 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/11 14:53:36 by johrober         ###   ########.fr       */
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

	if (argc == 1)
		export_without_args(shell);
	exit_status = EXIT_SUCCESS;
	i = 0;
	while (++i < argc)
	{
		if (is_valid_identifier(argv[i], 1))
			crea_mod_env_var(shell, argv[i]);
		else
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv[i]);
			exit_status = EXIT_FAILURE;
		}
	}
	return (exit_status);
}

int	unset(t_shell *shell, int argc, char **argv)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = EXIT_SUCCESS;
	while (++i < argc)
	{
		if (is_valid_identifier(argv[i], 0))
			remove_env_var(shell, argv[i]);
		else
		{
			ft_printf_fd(2, "unset: '%s': not a valid identifier\n", argv[i]);
			exit_status = EXIT_FAILURE;
		}
	}
	return (exit_status);
}
