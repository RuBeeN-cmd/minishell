/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:43:42 by johrober          #+#    #+#             */
/*   Updated: 2022/06/25 15:46:13 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <dirent.h>

# define BUILTIN_NB 4

typedef struct s_env_var {
	char	*name;
	char	*value;
}				t_env_var;

struct	s_shell;
typedef struct s_builtin {
	char	*name;
	void	(*f)(struct s_shell *shell, int argc, char **argv);
}				t_builtin;

typedef struct s_shell {
	/* int	running; */
	/* int	pid; */
	char			*prompt;
	char			*pwd;
	struct termios	termios_shell;
	t_builtin		*builtin_list[BUILTIN_NB + 1];
	t_env_var		**env;
}				t_shell;

typedef struct s_cmd {
	int		argc;
	char	**argv;
	//redirection
}				t_cmd;

//////////////////////////////////////////////////
////////////		minishell		//////////////
//////////////////////////////////////////////////

/********	main.c	*******************/
int			main(int argc, char **argv, char **env);

/********	signal_handler.c	*******/
void		set_signal_handlers(void);
void		receive(int signum);

/********	tshell.c		***********/
t_shell		*init_tshell(char **env);
void		destroy_tshell(t_shell *shell);

//////////////////////////////////////////////////
////////////		tenv			//////////////
//////////////////////////////////////////////////

/********	tenv_init.c		***********/
t_env_var	*init_env_var(char *name, char *value);
t_env_var	*parse_env_var(char *env_str);
t_env_var	**init_env(char **env_str);

/********	tenv_destroy.c		***********/
void		destroy_env_var(t_env_var *var);
void		destroy_env(t_env_var **env);

/********	tenv_utils.c		***********/
t_env_var	*get_env_var(t_shell *shell, char *name);
void		add_env_var(t_shell	*shell, char *name, char *value);
void		set_env_var(t_shell *shell, char *name, char *value);
void		print_env(t_shell *shell);
void		remove_env_var(t_shell *shell, char *name);

//////////////////////////////////////////////////
////////////		tcmd			//////////////
//////////////////////////////////////////////////

t_cmd		*init_cmd(void);
void		destroy_cmd(t_cmd *cmd);

//////////////////////////////////////////////////
////////////		built in		//////////////
//////////////////////////////////////////////////

/**	builtin_handler	**/
t_builtin	*init_builtin(char *name,
				void (*f)(t_shell *shell, int argc, char **argv));
void		init_builtin_list(t_shell *shell);
void		destroy_builtin_list(t_shell *shell);

/**	builtin_basics	**/
void		pwd(t_shell *shell, int argc, char **argv);
void		cd(t_shell *shell, int argc, char **argv);
//		echo
//		exit

/**	builtin_env		**/
void		unset(t_shell *shell, int argc, char **argv);
void		env(t_shell *shell, int argc, char **argv);
void		export(t_shell *shell, int argc, char **argv);

#endif
