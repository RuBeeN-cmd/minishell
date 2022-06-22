/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:36:31 by johrober          #+#    #+#             */
/*   Updated: 2022/06/22 12:45:39 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_cmd	*init_cmd(char	*function, char **arguments)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->function = function;
	cmd->arguments = arguments;
	return (cmd);
}

void	destroy_cmd(t_cmd	*cmd)
{
	free(cmd->function);
	ft_free_tab((void **)cmd->arguments);
	free(cmd);
}
