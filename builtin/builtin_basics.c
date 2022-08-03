/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:33:38 by johrober          #+#    #+#             */
/*   Updated: 2022/08/02 13:40:43 by rrollin          ###   ########.fr       */
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
		return (EXIT_SUCCESS);
	}
	else
		ft_printf_fd(2, "pwd: too many arguments\n");
	return (EXIT_FAILURE);
}

int	cd(t_shell *shell, int argc, char **argv)
{
	int			ret;
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	char		*path;

	if (argc == 2)
	{
		pwd = get_env_var(shell, "PWD");
		old_pwd = get_env_var(shell, "OLDPWD");
		path = argv[1];
		if (old_pwd && pwd)
			replace_old_pwd(pwd, old_pwd);
		ret = chdir(path);
		if (pwd)
			pwd->value = getcwd(pwd->value, 0);
		if (ret != -1)
			return (EXIT_SUCCESS);
		else
			perror("cd");
	}
	else
		ft_printf_fd(2, "cd: wrong number of arguments\n");
	return (EXIT_FAILURE);
}

int	word_contain_only(char *str, char c)
{
	if (str)
	{
		while (*str)
		{
			if (*str != c)
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
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
		while (argv[i] && argv[i][0] == '-')
		{
			if (word_contain_only(argv[i] + 1, 'n'))
			{
				n_flag = 1;
				i++;
			}
			else
				break ;
		}
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
	return (EXIT_SUCCESS);
}
// exit max : 9223372036854775807
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
		{
			ft_printf_fd(2, "exit: numeric argument required\n");
			destroy_tshell(shell);
			exit(2);
		}
		i++;
	}
	destroy_tshell(shell);
	exit(exit_status);
}
