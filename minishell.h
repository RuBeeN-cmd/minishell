/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:43:42 by johrober          #+#    #+#             */
/*   Updated: 2022/07/21 20:22:43 by johrober         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <libft.h>
# include <dirent.h>
# include <fcntl.h>

# define BUILTIN_NB	7
# define PARENTHESIS_NB	20

typedef struct s_env_var {
	char	*name;
	char	*value;
}				t_env_var;

struct	s_shell;
typedef struct s_builtin {
	char	*name;
	void	(*f)(struct s_shell *shell, int argc, char **argv);
}				t_builtin;

enum e_redir_type {APPEND, REPLACE, IN, UNTIL};
typedef	enum e_redir_type t_redir_type;

typedef struct s_redir
{
	char			*str;
	t_redir_type	type;
}				t_redir;

typedef struct s_cmd {
	int		argc;	
	char	**argv;
	char	**env;
	t_redir	**redir_tab;
}				t_cmd;

enum e_elem_type {WORD, REDIRECT, OPERATOR, PIPE, PARENTHESIS};
typedef enum e_elem_type	t_elem_type;

typedef struct s_cmd_element {
	char					*str;
	t_elem_type				type;
	struct s_cmd_element	*next;
}				t_cmd_element;

typedef struct s_shell {
	char			*prompt;
	char			*pwd;
	int				exit_status;
	int				fork;
	struct termios	termios_shell;
	t_builtin		*builtin_list[BUILTIN_NB + 1];
	t_cmd			**cmd_tab;
	t_env_var		**env;
}				t_shell;

//////////////////////////////////////////////////
////////////		minishell		//////////////
//////////////////////////////////////////////////

/********	main.c	*******************/
int				main(int argc, char **argv, char **env);

/********	signal_handler.c	*******/
void			set_signal_handlers(void);
void			receive(int signum);

/********	tshell.c		***********/
t_shell			*init_tshell(char **env);
void			destroy_tshell(t_shell *shell);

//////////////////////////////////////////////////
////////////		tenv			//////////////
//////////////////////////////////////////////////

/********	tenv_init.c		***********/
t_env_var		*init_env_var(char *name, char *value);
t_env_var		*parse_env_var(char *env_str);
t_env_var		**init_env(char **env_str);

/********	tenv_destroy.c		***********/
void			destroy_env_var(t_env_var *var);
void			destroy_env(t_env_var **env);
void			remove_env_var(t_shell *shell, char *name);

/********	tenv_utils.c		***********/
t_env_var		*get_env_var(t_shell *shell, char *name);
void			add_env_var(t_shell	*shell, char *name, char *value);
void			set_env_var(t_shell *shell, char *name, char *value);
void			print_env(t_shell *shell);
char			**env_to_string_array(t_shell *shell);

//////////////////////////////////////////////////
////////////		cmdparsing		//////////////
//////////////////////////////////////////////////

/****		tcmd.c		****/
t_cmd			*init_cmd(void);
void			destroy_cmd(t_cmd *cmd);
void			print_cmd(t_cmd *cmd);
t_redir			*init_redir(char *str, char *redir_type);
void			destroy_redir(t_redir *redir);

/***		t_cmd_element.c		******/
t_cmd_element	*init_element(char *str, t_elem_type type);
void			destroy_element(t_cmd_element *elem);
void			destroy_element_list(t_cmd_element *elem);
t_cmd_element	*detach_element(t_cmd_element **list, t_cmd_element *elem);
void			print_element(t_cmd_element *elem);
void			print_element_list(t_cmd_element *elem);

/***		cmd_splitting.c		******/
t_cmd_element	*split_into_element_list(t_shell *shell, char *str);
t_cmd_element	*parse_element_at(t_shell *shell, char **str);
t_cmd_element	*parse_word_element(t_shell *shell, char **str);
char			*parse_substring(t_shell *shell, char *str, int length);
char			*parse_var_call(t_shell *shell, char **str);

/***		cmd_wildcards.c		******/
void			handle_wildcards(t_cmd_element **list);
t_cmd_element	*replace_cmd_elements_by(t_cmd_element *current, char **matching_files);
char			**get_matching_files(char *expr);
int				is_matching_wildcard(char *name, char *expr);
int				advance_in_word(char **name, char **expr, int length, char *match);

/***		cmd_syntax_check.c	******/
int				is_syntax_valid(t_cmd_element *list);
int				is_parenthesis_syntax_valid(t_cmd_element *list);

/***		cmd_parse_final.c	*******/
t_cmd			**parse_final(t_cmd_element *list);
t_cmd			*parse_single_cmd(t_cmd_element *list);
t_redir			**parse_redirections(t_cmd_element *list);


//////////////////////////////////////////////////
////////////		built in		//////////////
//////////////////////////////////////////////////

/**	builtin_handler	**/
t_builtin		*init_builtin(char *name,
					void (*f)(t_shell *shell, int argc, char **argv));
void			init_builtin_list(t_shell *shell);
void			destroy_builtin_list(t_shell *shell);
int				call_builtin_if_exists(t_shell *shell, t_cmd *cmd);

/**	builtin_basics	**/
void			pwd(t_shell *shell, int argc, char **argv);
void			cd(t_shell *shell, int argc, char **argv);
void			echo(t_shell *shell, int argc, char **argv);
void			exit_builtin(t_shell *shell, int argc, char **argv);

/**	builtin_env		**/
void			unset(t_shell *shell, int argc, char **argv);
void			env(t_shell *shell, int argc, char **argv);
void			export(t_shell *shell, int argc, char **argv);

//////////////////////////////////////////////////
////////////		file     		//////////////
//////////////////////////////////////////////////

/**  file_utils  **/
void			write_mode(char *path, char *str, int mode);
void			append_file(char *path, char *str);
void			replace_file(char *path, char *str);

//////////////////////////////////////////////////
////////////		execution  		//////////////
//////////////////////////////////////////////////

/**	execute_pipelines.c	**/
pid_t			execute(t_shell *shell, t_cmd **list);
int				fork_cmd(t_shell *shell, t_cmd *cmd, int *input, int *output);
int				execute_cmd(t_shell *shell, t_cmd *cmd);
char			*search_executable_path(t_shell *shell, char *exec);
char			*try_path(char *path, char *exec);

/**	pipe_utils.c		**/
void			copy_pipe_from(int *dest, int *src);
void			init_pipe(int *pipe);
void			close_fd(int *fd);
int				count_pipes(t_cmd_element *list);

/**  exec.c  **/
int				ft_exec_bloc(t_shell *shell, t_cmd_element *input);
int				is_single_cmd(t_cmd_element *cmd);
int				exec(t_shell *shell, t_cmd_element *cmd);

/**  check_parenthesis.c  **/
void			remove_parenthesis(t_cmd_element **input);
int				got_parenthesis(t_cmd_element *input);
void			remove_pipe_parenthesis(t_cmd_element **input);

/**  split_cmd.c  **/
int				ft_split_cmd(t_shell *shell, t_cmd_element *input);
void			ft_get_blocks(t_cmd_element *input, t_cmd_element **cmd,
					t_cmd_element **operator, t_cmd_element **nxt_block);

#endif
