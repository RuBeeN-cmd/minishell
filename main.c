/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:26 by johrober          #+#    #+#             */
/*   Updated: 2022/07/01 14:59:11 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_element *create_elem(char *str, t_elem_type type)
{
	t_cmd_element *input = malloc((sizeof(t_cmd_element)));
	input->str = str;
	input->type = type;
	input->next = NULL;
	return (input);
}

void test(void)
{
	t_cmd_element *input;
	t_cmd_element *tmp;

	tmp = create_elem(ft_strdup("cat"), WORD);
	input = tmp;
	tmp->next = create_elem(ft_strdup("usgvjls"), WORD);
	tmp = tmp->next;
	tmp->next = create_elem(ft_strdup("&&"), OPERATOR);
	tmp = tmp->next;
	tmp->next = create_elem(ft_strdup("("), PARENTHESIS);
	tmp = tmp->next;
	tmp->next = create_elem(ft_strdup("echo"), WORD);
	tmp = tmp->next;
	tmp->next = create_elem(ft_strdup("&&"), OPERATOR);
	tmp = tmp->next;
	tmp->next = create_elem(ft_strdup("cat"), WORD);
	tmp = tmp->next;
	tmp->next = create_elem(ft_strdup(")"), PARENTHESIS);
	ft_exec_bloc(input);
}

int	main(int argc, char **argv, char **env)
{
	char			*str;
	t_shell			*shell;

	(void) argc;
	(void) argv;
	shell = init_tshell(env);
	set_signal_handlers();
	str = readline(shell->prompt);
	while (str && 0)
	{
		add_history(str);
		free(str);
		str = readline(shell->prompt);
	}
	test();
	destroy_tshell(shell);
	printf("exit\n");
}

/** Not used currently **/
void	clean_exit(t_shell *shell, int exit_code)
{
	destroy_tshell(shell);
	exit(exit_code);
}
