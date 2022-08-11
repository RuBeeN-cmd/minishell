/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttmpfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:18:26 by johrober          #+#    #+#             */
/*   Updated: 2022/08/11 15:23:44 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tmpfile	*init_tmpfile(char *name)
{
	t_tmpfile	*new_tmpfile;

	new_tmpfile = malloc(sizeof(t_tmpfile));
	new_tmpfile->name = name;
	new_tmpfile->next = NULL;
	new_tmpfile->fd = -2;
	return (new_tmpfile);
}
