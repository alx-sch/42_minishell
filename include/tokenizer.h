/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:36:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/30 13:08:52 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines the structures and functions used for tokenizing
input commands in our minishell. It includes definitions for token types,
the token structure, and a structure to manage tokens.

The tokenizer is responsible for parsing input commands into tokens, each
of which represents a distinct syntactic unit, such as a command, operator,
or redirection. These tokens are then stored in a linked list for further
processing by other components of the shell.
*/

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef struct s_data	t_data;

//	++++++++++++++++
//	++ STRUCTURES ++
//	++++++++++++++++

/**
Data type `enum` defines a set of constants via integers (starting with 0).
Categorizes tokens:

- PIPE:			'|' ; pipeline between two commands.
- REDIR_IN:		'<'	; redirects input of a command from a file instead of STDIN.
- REDIR_OUT:	'>' ; redirects output of a command into file instead of STDOUT.
- REDIR_APPEND:	'>>'; appends cmd output to a file without truncating it.
- HEREDOC:		'<<'; creates a here-document, directly input via CL.
- OTHER:		All other types.
*/
typedef enum e_token_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	HEREDOC,
	OTHER,
}	t_token_type;

/**
Represents a single token.

- type [t_token]:	Type of the token (e.g., PIPE, REDIR_IN, etc.).
- lexeme [char*]:	The actual string value of the token extracted from the input.
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
- tok [t_token*]:	The current token being processed, containing its type,
					lexeme, and position.
- new_node [t_list*]:	Pointer to the new node to be added to the token list,
						created from the current token.
- tok_lst [t_list*]:	Pointer to the head of the linked list of tokens, which
						stores all tokens parsed from the input.
- tmp [char*]:	Substring to extract content for OTHER tokens.
- quote [char]:	Saves encountered quotation symbols.
*/
typedef struct s_tok
{
	t_token	*tok;
	t_list	*new_node;
	t_list	*tok_lst;
	char	*tmp;
	char	quote;
}	t_tok;

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// tokenizer.c

int		get_tokens(t_data *data);
t_list	*create_tok(t_data *data, t_token_type type, const char *lexeme,
			int *i);

// tokenizer_pipe.c

int		is_pipe(t_data *data, int *i);

// tokenizer_redirection.c

int		is_redirection(t_data *data, int *i);

// tokenizer_utils.c

int		is_delimiter(t_data *data, const char c);

#endif
