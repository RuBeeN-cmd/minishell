/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipelines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:39:08 by johrober          #+#    #+#             */
/*   Updated: 2022/08/04 16:17:44 by johrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_shell *shell)
{
	int		nb_pipe;
	int		input[2];
	int		output[2];
	int		count;
	int		ret;

	nb_pipe = ft_tablen((const void **)shell->cmd_tab) - 1;
	init_pipe((int *)input);
	count = -1;
	while (++count <= nb_pipe)
	{
		ret = init_redirections(shell->cmd_tab[count]);
		init_pipe((int *)output);
		if (nb_pipe > 0 && count < nb_pipe)
			pipe(output);
		if (!ret)
			fork_cmd(shell, shell->cmd_tab[count], (int *)input, (int *)output);
		close_fd((int *)input);
		close_fd((int *)output + 1);
		close_redirections(shell, shell->cmd_tab[count]);
		copy_pipe_from((int *)input, (int *)output);
	}
	close_fd((int *)input + 1);
}

void	fork_cmd(t_shell *shell, t_cmd *cmd, int *input, int *output)
{
	remove_signal_handlers();
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
	else if (!cmd->pid)
	{
		
		shell->fork = 1;
		if (input[0] != -1)
		{
			dup2(input[0], STDIN_FILENO);
			close(input[0]);
		}
		if (output[1] != -1)
		{
			dup2(output[1], STDOUT_FILENO);
			close(output[0]);
			close(output[1]);
		}
		execute_cmd(shell, cmd);
	}
}

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*exec_path;

	cmd->env = env_to_string_array(shell);
	if (!ft_str_contains(cmd->argv[0], '/'))
	{
		call_builtin_if_exists(shell, cmd);
		exec_path = search_executable_path(shell, cmd->argv[0]);
		if (!exec_path)
		{
			ft_printf_fd(2, "%s: command not found.\n", cmd->argv[0]);
			close_redirections(shell, cmd);
			destroy_tshell(shell);
			exit(127);
		}
		free(cmd->argv[0]);
		cmd->argv[0] = exec_path;
	}
	set_redirections(shell, cmd);
	execve(cmd->argv[0], cmd->argv, cmd->env);
	close_redirections(shell, cmd);
	destroy_tshell(shell);
	perror(cmd->argv[0]);
	exit(EXIT_FAILURE);
}

char	*search_executable_path(t_shell *shell, char *exec)
{
	t_env_var	*path;
	char		**path_tab;
	char		*exec_path;
	int			count;

	exec_path = NULL;
	if (!ft_str_contains(exec, '/'))
	{
		path = get_env_var(shell, "PATH");
		if (path)
		{
			path_tab = ft_split(path->value, ':');
			count = -1;
			while (path_tab[++count] && !exec_path)
				exec_path = try_path(path_tab[count], exec);
			ft_free_tab((void **)path_tab);
		}
	}
	return (exec_path);
}

char	*try_path(char *path, char *exec)
{
	char	*exec_path;

	exec_path = NULL;
	if (ft_strlen(path))
		exec_path = ft_strnjoin(exec_path, path, ft_strlen(path));
	if (ft_strlen(exec_path) && exec_path[ft_strlen(exec_path) - 1] != '/')
		exec_path = ft_strnjoin(exec_path, "/", 1);
	exec_path = ft_strnjoin(exec_path, exec, ft_strlen(exec));
	if (!access(exec_path, F_OK) && ft_strlen(exec))
		return (exec_path);
	else
		free(exec_path);
	return (NULL);
}
