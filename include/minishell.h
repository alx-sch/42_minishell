/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 17:19:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
The  header file serves as the primary inclusion point for the project,
aggregating necessary headers and declarations. As it centralizes all the
essential includes, function prototypes, and data structs, this file ensures
that  each source file within the minishell projecthas access to the necessary
functionality without redundant includes.
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
# include "signals.h" // TBD

# include <fcntl.h> // open, close, access, unlink
# include <stdio.h> // perror, printf
# include <errno.h> // errno
# include <sys/wait.h> // waitpid
# include <sys/ioctl.h> // ioctl(), TIOCSTI
# include <readline/readline.h> // reading/editing input lines
# include <readline/history.h> // tracking/accessing previous command lines
# include <signal.h> // signal/sig fcts, kill
# include <termio.h> // provides struct termios used for terminal control

/**
Global variable used to indicate if the CTRL+C signal was received.
 - `0`: No signal received
 - `1`: CTRL+C (SIGINT) signal received

Declared as `volatile` so that the compiler always reads the latest value
directly from memory, as the variable may be changed by different parts
of the program.

The type `__sig_atomic_t` is designed for variables that are accessed and
modified by signal handlers: It guarantees atomic operations, preventing race
conditions and ensuring consistency when the variable is accessed from
different contexts.
*/
extern volatile __sig_atomic_t	g_signal;

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// 0: Initialization of Data Structures -> see init.h
// 1: Validation of user input (empty? open quotes?) -> see input_check.h
// 2: Tokenization of user input into distinct syntactic unit -> see tokenizer.h
// 3: Parsing of tokens (handling of heredocs and var expansion) -> see parser.h
// 4: Custoum built-in fcts for our minishell -> see builtins.h
// 5: Command exectuion (incl. forking / piping) -> see execution.h
// 6: Signal handling -> see singals.h

// 7_utils/utils.c

int		is_whitespace(int c);
int		contains_quotes(const char *str);
void	set_path_to_file(t_data *data, char **str, char *file, char *err_msg);
void	minishell_prompt(t_data *data);
void	print_token_list(t_list *lst);

// 7_utils/errors.c

void	print_err_msg(char *msg);
void	print_err_msg_prefix(char *msg);
void	print_err_msg_custom(char *msg, unsigned int print_newline);

// 7_utils/free.c

void	del_token(void *content);
void	free_unlinked_token(t_data *data);
void	free_data(t_data *data, bool exit);

// 8_history/history.c

void	add_history_to_file(char *input, char *path_to_hist_file);
char	*init_history(t_data *data);

#endif
