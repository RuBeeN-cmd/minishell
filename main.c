/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:26 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 15:44:14 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_interrupt = 0;

static void	handle_interrupt(t_shell *shell)
{
	shell->interrupt = 0;
	if (g_interrupt == 1)
	{
		shell->exit_status = 130;
		g_interrupt = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	char			*str;
	t_shell			*shell;
	t_cmd_element	*list;

	(void) argc;
	(void) argv;
	shell = init_tshell(env);
	set_signal_handlers();
	str = readline(shell->prompt);
	while (str)
	{
		handle_interrupt(shell);
		list = split_into_element_list(shell, str);
		if (is_syntax_valid(list))
		{
			create_all_heredocs(shell, list);
			ft_exec_bloc(shell, list, 1);
		}
		if (ft_strlen(str))
			add_history(str);
		free(str);
		str = readline(shell->prompt);
	}
	destroy_tshell(shell);
	printf("exit\n");
}
