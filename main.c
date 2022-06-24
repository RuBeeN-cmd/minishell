/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:26 by johrober          #+#    #+#             */
/*   Updated: 2022/06/23 16:52:50 by johrober         ###   ########.fr       */
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
	t_shell			shell;
	int				ret;
	char			**cat_arg;
	pid_t			pid;

	(void) argc;
	(void) argv;
	init_tshell(&shell, env);
	set_signal_handlers();
	str = readline(shell.prompt);
	while (str)
	{
		printf("%s\n", str); // <--- parse str & exec
		add_history(str);
		if (!strcmp(str, "cat"))
		{
			cat_arg = malloc(sizeof(char *) * 3);
			cat_arg[0] = "cat";
			cat_arg[1] = "file*";
			cat_arg[2] = NULL;
			pid = fork();
			if (!pid)
			{
				ret = execve("/usr/bin/cat", cat_arg, env);
				if (ret == -1)
					perror("execve ");
			}
			free(cat_arg);
		}
		free(str);
		str = readline(shell.prompt);
	}
	destroy_tshell(&shell);
	printf("exit\n");
}

void	clean_exit(t_shell *shell, int exit_code)
{
	destroy_tshell(shell);
	exit(exit_code);
}
