/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/29 19:26:19 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h" // libft
# include "errors.h" // prompt, etc.
# include "config.h" // error messages
# include "tokenizer.h"
# include "parser.h"

# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open, close, read, write, access, unlink
# include <stdio.h> // perror, printf
# include <string.h> // strerror
# include <errno.h> // errno
# include <unistd.h> // fork, pipe, execve, macros like 'STDERR_FILENO' etc.
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/ioctl.h> // ioctl
# include <readline/readline.h> // reading/editing input lines
# include <readline/history.h> // tracking/accessing previous command lines
# include <signal.h> // signal/sig fcts, kill
# include <dirent.h> // opendir, readdir, closedir
# include <termios.h> // tcsetattr, tcgetattr
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

//	++++++++++++++++
//	++ STRUCTURES ++
//	++++++++++++++++

typedef struct s_cd
{
	char	*subdirectory;
	char	*home_user;
	char	*parentdirectory;
	char	**component;
}	t_cd;

/*
- char	*input:		The input string containing the command line input.
- char	quote:		Encountered quotation symbol (single or double) in input.
- int	pipe_no:	The number of pipes in the input string.
*/
typedef struct s_env
{
	char			*value;
	char			*e_var;
	struct s_env	*next;
	struct s_env	*previous;
	bool			printed;
}	t_env;

/*
TBD
*/
typedef struct s_data
{
	int			argc;
	char		**argv;
	char		**envp;
	char		*input;
	char		*tmp;
	char		quote;
	int			pipe_nr;
	t_tok		tok;
	t_cd		cd;
	t_env		*envp_temp;
	t_env		*export_list;
}	t_data;

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// Struct initializations

void			init_cd_struct(t_cd **cd, char *input);
t_env			*init_env_tmp(char **envp);
t_env			*init_export_list(t_data *data);
void			init_data_struct(t_data *data, \
int argc, char **argv, char **envp);

// utils.c

int				is_whitespace(int c);
void			print_err_msg(char *msg);
void			print_token_list(t_list *lst); // TESTING ONLY

//	0_check_input/check_input.c

int				is_input_empty(char *input);
int				is_quotation_closed(t_data *data);

// 2_parser

int				expand_variables(char **str, t_env *env_list);

// free.c

void			del_token(void *content);
void			free_unlinked_token(t_data *data);
void			free_data(t_data *data, bool exit);

// Parsing:

void			parsing(t_data *data);
int				is_pwd(char *input);
int				is_cd(char *input);
int				is_exit(t_data *data);
int				is_env(char *input);
int				is_unset(char *input);
int				is_export(char *input);
int				is_echo(char *input);

// Builtins:

void			init_cd_struct(t_cd **cd, char *input);
t_env			*init_env_tmp(char **envp);
int				cd(char *input, t_env *envp_temp);
void			pwd(void);
void			env(t_env *env_temp);
void			unset(char *input, t_env **envp_temp);
unsigned int	exit_with_code(t_data *data);
void			export(t_data *data);
void			minishell_echo(t_data *data);

// Butiltins utils:

void			add_env_var_no_value(t_data *data, char *arg);
void			add_env_var_export_with_value(t_data *data, char *arg);
void			add_env_var_envp_with_value(t_data *data, char *arg);
void			ft_env_tmp_add_back(t_env **head, t_env *new);

// Modified standard functions:

int				ft_strchr_index(const char *s, int c);
int				ft_strrchr_index(const char *s, int c);
bool			is_only_duplicates(char *s, char c);
int				is_letter(char c);

// Counting-functions:

int				count_array_length(char **array);

// Freeing allocated memory for builtins:

int				ft_freearray(char **arr);
int				too_many_args_cd(t_cd **cd);
int				free_cd_struct(t_cd **cd);
void			free_env_struct(t_env **head);

// Errors:

void			print_error_cd(int error_code, t_cd **cd);
void			print_error_exit(t_data *data);
int				env_error_messages(char *input, int i);
void			mem_alloc_fail_env(t_env **head);
void			exit_check_argc(t_data *data);
int				export_err_invalid_option(char *input, int i);
void			unset_err_memalloc_fail(t_env **envp_temp);
int				unset_err_invalid_option(char *input, int i);
int				pwd_invalid_option(char *input, int i);
void			export_mem_alloc_failure(t_data *data);

#endif
