/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:36:59 by johrober          #+#    #+#             */
/*   Updated: 2022/08/06 14:02:04 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_handlers(void)
{
	signal(SIGINT, &receive);
	signal(SIGQUIT, &receive);
}

void	remove_signal_handlers(void)
{
	signal(SIGINT, &receive_while_forked);
	signal(SIGQUIT, &receive_while_forked);
}

void	receive_while_forked(int signum)
{
	if (signum == SIGINT)
		printf("\n");
}

void	receive(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
