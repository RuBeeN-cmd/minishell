/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:42:07 by johrober          #+#    #+#             */
/*   Updated: 2022/07/29 11:48:27 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_builtin	*init_builtin(char *name,
		int (*f)(t_shell *shell, int argc, char **argv))
{
	t_builtin	*new;

	new = malloc(sizeof(t_builtin));
	new->name = name;
	new->f = f;
	return (new);
}

void	init_builtin_list(t_shell *shell)
{
	shell->builtin_list[0] = init_builtin("cd", &cd);
	shell->builtin_list[1] = init_builtin("pwd", &pwd);
	shell->builtin_list[2] = init_builtin("env", &env);
	shell->builtin_list[3] = init_builtin("export", &export);
	shell->builtin_list[4] = init_builtin("unset", &unset);
	shell->builtin_list[5] = init_builtin("echo", &echo);
	shell->builtin_list[6] = init_builtin("exit", &exit_builtin);
	shell->builtin_list[7] = NULL;
}

void	destroy_builtin_list(t_shell *shell)
{
	int	count;

	count = -1;
	while (shell->builtin_list[++count])
		free(shell->builtin_list[count]);
}

int	call_builtin_if_exists(t_shell *shell, t_cmd *cmd)
{
	int			count;
	int			ret;
	t_builtin	*builtin;

	count = -1;
	builtin = NULL;
	ret = 0;
	while (++count < BUILTIN_NB && cmd->argc > 0)
	{
		if (!ft_strcmp(shell->builtin_list[count]->name, cmd->argv[0]))
		{
			builtin = shell->builtin_list[count];
			break ;
		}
	}
	if (!builtin && cmd->argc > 0)
		return (-1);
	if (!shell->fork)
		ret = init_redirections(cmd);
	set_redirections(shell, cmd);
	if (cmd->argc > 0 && !ret)
		ret = builtin->f(shell, cmd->argc, cmd->argv);
	if (shell->fork)
		exit(ret);
	close_redirections(shell, cmd);
	return (ret);
}
