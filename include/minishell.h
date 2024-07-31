/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/31 19:25:11 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h" // libft fcts, stdlib.h (malloc,..), unistd.h (e.g)

# include "config.h" // configuration constants, like color codes or prompts
# include "errors.h" // error messages and respective formatting
# include "types.h" // all data structure types, e.g. 't_data'

# include "init.h" // initialization of data structs as defined in types.h
# include "input_check.h" // checks if user input is valid (empty, open quotes)
# include "tokenizer.h" // procceses CL input into syntactic units (tokens)
# include "parser.h" // proccesses tokens (handling of heredoc and variables)
# include "builtins.h" // `cd`, `pwd`, `env`, `unset`, `export`, `echo` as fcts
# include "execution.h" // TBD

# include <fcntl.h> // open, close, access, unlink
# include <stdio.h> // perror, printf
# include <errno.h> // errno
# include <sys/wait.h> // waitpid
# include <readline/readline.h> // reading/editing input lines
# include <readline/history.h> // tracking/accessing previous command lines
# include <signal.h> // signal/sig fcts, kill

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// 0: Initialization of Data Structures -> see init.h
// 1: Validation of user input (empty? open quotes?) -> see input_check.h
// 2: Tokenization of user input into distinct syntactic unit -> see tokenizer.h
// 3: Parsing of tokens (handling of heredocs and var expansion) -> see parser.h
// 4: Custoum built-in fcts for our minishell -> see builtins.h
// 4: 

// utils.c

int				is_whitespace(int c);
void			print_err_msg(char *msg);
void			print_token_list(t_list *lst); // TESTING ONLY

// free.c

void			del_token(void *content);
void			free_unlinked_token(t_data *data);
void			free_data(t_data *data, bool exit);

// Parsing builtins:

int				parsing(t_data *data);
int				is_pwd(char *input);
int				is_cd(char *input);
int				is_exit(t_data *data);
int				is_env(char *input);
int				is_unset(char *input);
int				is_export(char *input);
int				is_echo(char *input);

#endif
