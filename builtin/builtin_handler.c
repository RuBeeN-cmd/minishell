/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:42:07 by johrober          #+#    #+#             */
/*   Updated: 2022/06/24 12:29:30 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_builtin	*init_builtin(char *name,
		void	(*f)(t_shell *shell, int argc, char **argv))
{
	t_builtin	*new;

	new = malloc(sizeof(t_builtin));
	new->name = name;
	new->f = f;
	return (new);
}

void	init_builtin_list(t_shell *shell)
{
	shell->builtin_list[0] = init_builtin("env", &env);
	shell->builtin_list[1] = init_builtin("cd", &cd);
	shell->builtin_list[2] = init_builtin("pwd", &pwd);
	shell->builtin_list[3] = NULL;
}
void	destroy_builtin_list(t_shell *shell)
{
	int	count;

	count = -1;
	while (shell->builtin_list[++count])
	{
		free(shell->builtin_list[count]);
	}
}
