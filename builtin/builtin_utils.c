/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:45:13 by rrollin           #+#    #+#             */
/*   Updated: 2022/07/29 12:14:49 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_old_pwd(t_env_var *pwd, t_env_var *old_pwd)
{
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = NULL;
	return ;
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

void	crea_mod_env_var(t_shell *shell, char **var)
{
	t_env_var	*env_var_ptr;

	env_var_ptr = get_env_var(shell, var[0]);
	if (env_var_ptr)
		env_var_ptr->value = var[1];
	else
		add_env_var(shell, var[0], var[1]);
}