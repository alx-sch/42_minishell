/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/22 16:07:59 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h" // libft
# include "errors.h" // prompt, etc.
# include "config.h" // error messages
# include "tokenizer.h" // prompt, etc.

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
	int		argc;
	char	**argv;
	char	**envp;
	char	*input;
	char	*tmp;
	char	quote;
	int		pipe_no;
	t_tok	tok;
	t_cd	cd;
	t_env	*envp_temp;
	t_env	*export_list;
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

void			print_heredoc_found(t_data *data);

// 0_check_input/check_quotation.c

int				is_quotation_closed(t_data *data);

// 0_tokenizer/tokenizer_redirection.c

int				is_redirection(t_data *data, int *i);

int				is_pipe(t_data *data, int *i);

// FOR TESTING!!
void			print_string_array(char **array);

// free.c

void			free_str_arr(char ***array_ptr);

// 0_tokenizer/tokenizer_expansion.c

char			*expand_variables(t_data *data);

// 0_lexer/lexer_main.c

char			**parser(char *input);

// tokenizer_utils.c

void			print_token(const t_list *current);
void			print_token_list(t_list *token_list);
int				is_whitespace(int c);
int				is_delimiter(t_data *data, const char c);

// free.c

void			del_token(void *content);
void			free_data(t_data *data);

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

int				cd(char *input, char **envp);
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

#endif
