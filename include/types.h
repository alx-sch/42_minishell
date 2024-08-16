/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:40:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/16 16:19:59 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file contains definitions of data structures and enums used
in the implementation of our minishell. It includes definitions for tokens
used in parsing commands and the execution as well as for built-ins.

The `t_data` structure encapsulates the overall state of the minishell,
including user input, token and built-in management, and environment variables.
*/

#ifndef TYPES_H
# define TYPES_H

# include "libft.h" // t_list
# include <stdbool.h> // bool

//	++++++++++++
//	++ TOKENS ++
//	++++++++++++

/**
Data type `enum` defines a set of constants via integers (starting with 0).
Categorizes tokens:

- PIPE :		'|' ; pipeline between two commands.
- REDIR_IN:		'<'	; redirects input of a command from a file instead of STDIN.
- REDIR_OUT:	'>' ; redirects output of a command into file instead of STDOUT.
- REDIR_APPEND:	'>>'; appends cmd output to a file without truncating it.
- HEREDOC :		'<<'; creates a here-document, directly input via CL.
- OTHER :		All other types.
- EMPTY_VAR:	Is variable and empty or only whitespace after expansion.
*/
typedef enum e_token_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	HEREDOC,
	OTHER,
	EMPTY_VAR
}	t_token_type;

/**
Represents a single token.

Fields:
- type [t_token]:	Type of the token (e.g., PIPE, REDIR_IN, etc.).
- lexeme [char*]:	The actual string value of the token extracted from
					the input.
- position [int]:	The position (index) of the token in the input string.
*/
typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	int				position;
}	t_token;

/**
Holds all information for managing tokens and the linked list of tokens.

This structure is used to maintain the state while processing tokens. Each token
of type `t_token` is stored in a `t_list` node via the 'content' member
(of type void*), using the ft_lstnew() function.

Fields:
- tok [t_token*]:		The current token being processed, containing its type,
						lexeme, and position.
- new_node [t_list*]:	Pointer to the new node to be added to the token list,
						created from the current token.
- tok_lst [t_list*]:	Pointer to the head of the linked list of tokens, which
						stores all tokens parsed from the input.
- tmp [char*]:			Substring to extract content for OTHER tokens.
- r_redir [int]:		Holds the return value of `is_redirection()` in
						`get_tokens()`.
- r_pipe [int]:			Holds the return value of `is_pipe()` in `get_tokens()`.
- r_other [int]:		Holds the return value of `add_other_token` in
						`get_tokens()`.
*/
typedef struct s_tok
{
	t_token	*tok;
	t_list	*new_node;
	t_list	*tok_lst;
	char	*tmp;
	char	quote;
	int		r_redir;
	int		r_pipe;
	int		r_other;
}	t_tok;

//	+++++++++++++
//	++ PARSING ++
//	+++++++++++++

/**
Holds information about whether the current parsing
context is inside single or double quotes.

Fields:
- in_single [bool]:	Flag indicating if the parser is currently inside
					single quotes (`true` if inside single quotes,
					`false` otherwise)
- in_double [bool]:	Flag indicating if the parser is currently inside
					double quotes (`true` if inside single quotes,
					`false` otherwise)
*/
typedef struct s_quote
{
	bool	in_single;
	bool	in_double;
}	t_quote;

//	+++++++++++++++
//	++ BUILT-INS ++
//	+++++++++++++++

typedef struct s_cd
{
	char	*subdirectory;
	char	*home_user;
	char	*parentdirectory;
}	t_cd;

typedef struct s_env
{
	char			*value;
	char			*e_var;
	struct s_env	*next;
	struct s_env	*previous;
	bool			printed;
}	t_env;

//	+++++++++++++++
//	++ EXECUTION ++
//	+++++++++++++++

typedef struct s_child
{
	pid_t	*nbr;
}	t_child;

typedef struct s_exec
{
	int		pipe_fd[2];
	int		prev_pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		curr_child;
	int		count_flags;
	char	**envp_temp_arr;
	char	**all_paths;
	char	*current_path;
	char	**input;
	char	*cmd;
	char	**flags;
	char	*infile;
	char	*outfile;
	bool	redir_in;
	bool	redir_out;
	bool	append_out;
	bool	first;
	bool	cmd_found;
	t_child	*child;
}	t_exec;

//	+++++++++++++++++
//	++ DATA STRUCT ++
//	+++++++++++++++++

/**
Holds all necessary information for managing the state of the minishell.

This structure encapsulates the state and context required for the minishell
to operate, including command-line arguments, environment variables, user input,
token management, and built-in command states.

Fields:
- argc [int]:			Number of arguments given to minishell.
- argv [char**]:		An array of argument variables passed to minishell.
- envp [char**]:		An array containing the initial state of the environment
						variables.
- input [char*]:		User input entered into the prompt.
- pipe_nr [int]:		The number of pipes in the current command.
- exit_status [unsigned int]:	The exit status of the last executed command.
- working_dir [char *]:	The project's working directory.
- tok [t_tok]:			Manages token status and holds the linked list of tokens.
- envp_temp [t_env*]:	A linked list containing the continuously modified state
						of the environment variables, used for the "env" command.
- export_list [t_env*]:	A linked list containing the continuously modified state
						of the environment variables that have been marked for
						export, including those without values, used for the
						'export' command.
- cd [t_cd]:			Used for the "cd" built-in command.
- quote [t_quote]		Parsing context is inside single or double quotes.
*/
typedef struct s_data
{
	int				argc;
	char			**argv;
	char			**envp;
	char			*input;
	int				pipe_nr;
	unsigned int	exit_status;
	char			*working_dir;
	char			*path_to_hist_file;
	t_tok			tok;
	t_env			*envp_temp;
	t_env			*export_list;
	t_cd			cd;
	t_quote			quote;
}	t_data;

#endif
