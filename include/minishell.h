/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/15 19:38:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h" // libft
# include "config.h" // prompt, etc.
# include "scanner.h" // prompt, etc.

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



// utils.c

// FOR TESTING!!
void	print_string_array(char **array);

// free.c
void	free_str_arr(char ***array_ptr);

// 0_lexer/lexer_main.c

char	**parser(char *input);

// lexer_utils.c

void	print_token(const t_list *current);
void	print_token_list(t_list *token_list);
int		is_space(int c);
int		is_input_empty(const char *input);
int		is_delimiter(const char c);

// 0_lexer/scanner.c

t_list	*get_tokens(const char *input);

// free.c

void	del_token(void *content);

#endif
