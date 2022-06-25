/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:26 by johrober          #+#    #+#             */
/*   Updated: 2022/06/25 14:26:28 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_shell *get_shell() */
/* { */
/* 	static t_shell shell; */

/* 	return (&shell); */
/* } */

int main(int argc, char **argv, char **env)
{
	char			*str = NULL;
	t_shell			*shell;

	(void) argc;
	(void) argv;
	shell = init_tshell(env);
	set_signal_handlers();
	str = readline(shell->prompt);
	while (str)
	{
		printf("%s\n", str); // <--- parse str & exec
		add_history(str);
		free(str);
		str = readline(shell->prompt);
	}
	destroy_tshell(shell);
	printf("exit\n");
}

/** Not used currently **/
void	clean_exit(t_shell *shell, int exit_code)
{
	destroy_tshell(shell);
	exit(exit_code);
}
