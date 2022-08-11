/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:36:31 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 18:26:43 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->env = NULL;
	cmd->tmpfile_name = NULL;
	cmd->interrupt = 0;
	cmd->redir_tab = NULL;
	cmd->pid = -1;
	cmd->status = -1;
	return (cmd);
}

void	destroy_cmd(t_cmd *cmd)
{
	if (cmd->argv)
		ft_destroy_tab((void ***)&cmd->argv, &free);
	if (cmd->redir_tab)
		ft_destroy_tab((void ***)&cmd->redir_tab,
			(void (*)(void *))destroy_redir);
	if (cmd->env)
		ft_destroy_tab((void ***)&cmd->env, &free);
	if (cmd->tmpfile_name)
		free(cmd->tmpfile_name);
	free(cmd);
}

void	print_cmd(t_cmd *cmd)
{
	int	count;

	printf("\tArgc\n\t\t%d\n", cmd->argc);
	printf("\tArgv\n");
	count = -1;
	while (cmd->argv && cmd->argv[++count])
		printf("\t\t%s\n", cmd->argv[count]);
	printf("\tRedirections\n");
	count = -1;
	while (cmd->redir_tab && cmd->redir_tab[++count])
	{
		printf("\t\tType\t");
		if (cmd->redir_tab[count]->type == e_replace)
			printf("Replace");
		if (cmd->redir_tab[count]->type == e_append)
			printf("Append");
		if (cmd->redir_tab[count]->type == e_in)
			printf("Infile");
		if (cmd->redir_tab[count]->type == e_until)
			printf("Until");
		printf("\t\t\tValue\t%s\n", cmd->redir_tab[count]->str);
	}
}

t_redir	*init_redir(char *str, char *redir_type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->str = ft_strdup(str);
	redir->fd = -2;
	if (!ft_strcmp(redir_type, ">"))
		redir->type = e_replace;
	else if (!ft_strcmp(redir_type, ">>"))
		redir->type = e_append;
	else if (!ft_strcmp(redir_type, "<"))
		redir->type = e_in;
	else if (!ft_strcmp(redir_type, "<<"))
		redir->type = e_until;
	return (redir);
}

void	destroy_redir(t_redir *redir)
{
	free(redir->str);
	free(redir);
}
