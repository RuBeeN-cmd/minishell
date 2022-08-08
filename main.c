/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:26 by johrober          #+#    #+#             */
/*   Updated: 2022/08/08 14:33:27 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		list = split_into_element_list(shell, str);
		if (is_syntax_valid(list))
			ft_exec_bloc(shell, list);
		else if (ft_strlen(str))
			ft_printf("Syntax error in command.\n");
		if (ft_strlen(str))
			add_history(str);
		free(str);
		str = readline(shell->prompt);
	}
	destroy_tshell(shell);
	//printf("exit\n");i
}
