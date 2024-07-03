/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:36:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/03 17:19:37 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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

/*
Data type `enum` defines a set of constants via integer (starting with 0).
Categorizes tokens / lexemes:
- OTHER:		Lexemes to be passed to execve(), may contain quotes and variables.
- PIPE:			'|' ; pipeline between two commands.
- REDIR_IN:		'<'	; redirects input of a command from a file instead of STDIN.
- REDIR_OUT:	'>' ; redirects output of a command into a file instead of STDOUT.
- REDIR_APPEND:	'>>'; appends cmd output to a file without truncating it.
- HEREDOC:		'<<'; creates a here-document, directly input via CL.
*/
typedef enum e_token_type
{
	OTHER,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	HEREDOC,
}	t_token_type;

/*
Represents a single token.
- t_token type:	Type of the token (e.g., PIPE, REDIR_IN, etc.).
- char *lexeme:	The actual string value of the token extracted from the input.
- int position:	The position (index) of the token in the input string.
*/
typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	int				position;
}	t_token;

/*
Holds all information for managing tokens and the linked list of tokens.

Tokens of type `t_token` are stored in a `t_list` node via the 'content'
member (of type void*), using the ft_lstnew() function.

- t_token tok:		The current token being processed, containing its type,
					lexeme, and position.
- t_list new_node:	Pointer to the new node to be added to the token list,
					created from the current token.
- t_list tok_lst:	Pointer to the head of the linked list of tokens, which
					stores all tokens parsed from the input.
*/
typedef struct s_tok
{
	t_token	*tok;
	t_list	*new_node;
	t_list	*tok_lst;
}	t_tok;

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// 0_tokenizer/tokenizer_get_tokens.c

int			get_tokens(t_data *data);
t_list		*create_tok(t_data *data, t_token_type type, const char *lexeme,
				int *i);

#endif
