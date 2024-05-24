/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/25 01:12:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_cd
{
	char	*username;
	char	*subdirectory;
	char	*home_user;
	char	*parentdirectory;
	char	**component;
}	t_cd;

/*
- char *input:		The input string containing the command line input.
*/
typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*input;
	char	*tmp;
	t_tok	tok;
	t_cd	cd;
}	t_data;


// utils.c

void	perror_and_exit(char *msg, t_data *data);
void	msg_and_exit(char *msg, t_data *data);

// 0_tokenizer/tokenizer_redirection.c

int		is_redirection(t_data *data, int *i);

// 0_tokenizer/scanner.c

t_list	*create_tok(t_data *data, t_token_type type, const char *lexeme,
			int *i);

// FOR TESTING!!
void	print_string_array(char **array);

// free.c

void	free_str_arr(char ***array_ptr);

// 0_tokenizer/tokenizer_expansion.c

char	*expand_variables(t_data *data);

// 0_lexer/lexer_main.c

char	**parser(char *input);

// lexer_utils.c

void	print_token(const t_list *current);
void	print_token_list(t_list *token_list);
int		is_space(int c);
int		is_input_empty(const char *input);
int		is_delimiter(const char c);

// 0_lexer/scanner.c

void	get_tokens(t_data	*data);

// free.c

void	del_token(void *content);
void	free_data(t_data **data_struct);


// Parsing:
void	parsing(char *input, char **envp);

// Builtins:
void	init_cd_struct(t_cd **cd, char *input);
void	cd(char *input, char **envp);
void	pwd(void);

// Modified standard functions:
int		ft_strrchr_index(const char *s, int c);
bool	is_only_duplicates(char *s, char c);

// Counting-functions:
int		count_array_length(char **array);

// Freeing allocated memory:
int		ft_freearray(char **arr);
void	free_cd_struct(t_cd **cd);

// Errors:
void	print_error_cd(int error_code, t_cd **cd);

#endif
