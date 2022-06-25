/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:33:38 by johrober          #+#    #+#             */
/*   Updated: 2022/06/25 15:38:19 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		old_pwd = get_env_var(shell, "OLDPWD");
		if (argc == 1)
			path = "~";
		else
			path = argv[1];
		if (old_pwd && pwd)
			old_pwd->value = pwd->value;
		ret = chdir(path);
		shell->pwd = getcwd(shell->pwd, 0);
		if (pwd)
			pwd->value = shell->pwd;
		if (ret == -1)
			perror("Error ");
	}
	else
		printf("cd: too many arguments");
}
