/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:33:38 by johrober          #+#    #+#             */
/*   Updated: 2022/08/09 11:48:32 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_shell *shell, int argc, char **argv)
{
	char	*pwd;

	(void)shell;
	(void)argv;
	pwd = NULL;
	if (argc == 1)
	{
		pwd = getcwd(pwd, 0);
		ft_printf("%s\n", pwd);
		free(pwd);
		return (exit_fork(shell, EXIT_SUCCESS));
	}
	else
		ft_printf_fd(2, "pwd: too many arguments\n");
	return (exit_fork(shell, EXIT_FAILURE));
}

int	cd(t_shell *shell, int argc, char **argv)
{
	int			ret;
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	char		*path;
	char		*value;

	if (argc == 2)
	{
		pwd = get_env_var(shell, "PWD");
		old_pwd = get_env_var(shell, "OLDPWD");
		path = argv[1];
		ret = chdir(path);
		replace_old_pwd(shell, pwd, old_pwd);
		value = NULL;
		value = getcwd(value, 0);
		if (!pwd)
			pwd = add_env_var(shell, ft_strdup("PWD"), value);
		pwd->value = value;
		if (ret != -1)
			return (exit_fork(shell, EXIT_SUCCESS));
		perror("cd");
	}
	else
		ft_printf_fd(2, "cd: wrong number of arguments\n");
	return (exit_fork(shell, EXIT_FAILURE));
}

int	echo(t_shell *shell, int argc, char **argv)
{
	int	n_flag;
	int	i;

	(void) shell;
	n_flag = 0;
	i = 1;
	if (argc == 1)
		ft_putchar_fd('\n', 1);
	else
	{
		n_flag = check_n_flag(argv, &i);
		while (i < argc)
		{
			ft_putstr_fd(argv[i], 1);
			if (i < argc - 1)
				ft_putchar_fd(' ', 1);
			if (!n_flag && i == argc - 1)
				ft_putchar_fd('\n', 1);
			i++;
		}
	}
	return (exit_fork(shell, EXIT_SUCCESS));
}

int	exit_builtin(t_shell *shell, int argc, char **argv)
{
	unsigned char	exit_status;
	int				i;

	(void)argc;
	i = 1;
	if (argc == 1)
	{
		destroy_tshell(shell);
		exit(EXIT_SUCCESS);
	}
	while (argv[i])
	{
		if (i == 2)
		{
			ft_printf_fd(2, "exit: too many arguments\n");
			return (EXIT_FAILURE);
		}
		if (ft_isnumber(argv[i]))
			exit_status = (unsigned char) ft_atoi(argv[1]);
		else
			exit_non_num_arg(shell);
		i++;
	}
	destroy_tshell(shell);
	exit(exit_status);
}
