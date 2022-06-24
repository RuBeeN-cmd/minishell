/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:33:38 by johrober          #+#    #+#             */
/*   Updated: 2022/06/23 16:26:49 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *shell, int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		if (!shell->pwd)
			shell->pwd = getcwd(shell->pwd, 0);
		ft_printf("%s\n", shell->pwd);
	}
	else
		printf("pwd: too many arguments\n");
}

void	cd(t_shell *shell, int argc, char **argv)
{
	int			ret;
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	char		*path;

	if (argc == 1 || argc == 2)
	{
		pwd = get_env_var(shell, "PWD");
		old_pwd = get_env_var(shell, "OLD_PWD");
		if (argc == 1)
			path = "~";
		else if (!strcmp(argv[1], "-"))
			path = old_pwd->value;	//Need a check to see if OLD_PWD is set, else send an error
		else
			path = argv[1];
		old_pwd->value = pwd->value;
		ret = chdir(path);
		pwd->value = getcwd(pwd->value, 0);
		shell->pwd = pwd->value;
		if (ret == -1)
			perror("Error ");
	}
	else
		printf("cd: too many arguments");
}

void	env(t_shell *shell, int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		print_env(shell);
	}
	else
		printf("env: too many arguments");
}
