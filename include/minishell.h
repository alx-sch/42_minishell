/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/12 11:26:40 by aschenk          ###   ########.fr       */
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
	struct s_env	*next;
	struct s_env	*previous;
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
}	t_data;

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

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
int				is_exit(char *input);
int				is_env(char *input);
int				is_unset(char *input);

// Builtins:

void			init_cd_struct(t_cd **cd, char *input);
t_env			*init_env_tmp(char **envp);
int				cd(char *input, char **envp);
void			pwd(void);
void			env(t_env *env_temp);
void			unset(char *input, t_env **envp_temp);
unsigned int	exit_with_code(char *input);

// Modified standard functions:
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
void			print_error_exit(char *input);
void			exit_check_argc(char *input);

#endif
