/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:45:13 by rrollin           #+#    #+#             */
/*   Updated: 2022/08/09 15:01:21 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_old_pwd(t_shell *shell, t_env_var *pwd, t_env_var *old_pwd)
{
	if (old_pwd)
	{
		if (pwd)
		{
			free(old_pwd->value);
			old_pwd->value = pwd->value;
			pwd->value = NULL;
		}
		else
			remove_env_var(shell, "OLDPWD");
	}
	else if (pwd)
		add_env_var(shell, ft_strdup("OLDPWD"), pwd->value);
}

int	ft_isnumber(const char *str)
{
	size_t		count;
	long long	total;

	if (!ft_strcmp(str, "-9223372036854775808"))
		return (1);
	total = 0;
	count = str[0] == '-';
	while (str[count] >= '0' && str[count] <= '9')
	{
		if (total * 10 + (str[count] - '0') < total)
			return (0);
		total = total * 10 + (str[count] - '0');
		count++;
	}
	return (!str[count]);
}

void	crea_mod_env_var(t_shell *shell, char *str)
{
	char		**var;
	t_env_var	*env_var_ptr;

	var = get_var_export(str);
	env_var_ptr = get_env_var(shell, var[0]);
	if (env_var_ptr)
		env_var_ptr->value = var[1];
	else
	{
		if (var[1])
			add_env_var(shell, var[0], var[1]);
		else
			free(var[0]);
	}
	free(var);
}

int	check_n_flag(char **argv, int *i)
{
	int	n_flag;

	n_flag = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		if (word_contain_only(argv[*i] + 1, 'n'))
		{
			n_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (n_flag);
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
