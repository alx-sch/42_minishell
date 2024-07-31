/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:36:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/31 18:40:17 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines functions used for tokenizing input commands in our
minishell. It includes definitions for token types, the token structure, and
a structure to manage tokens.

The tokenizer is responsible for parsing input commands into tokens, each
of which represents a distinct syntactic unit, such as a command, operator,
or redirection. These tokens are then stored in a linked list for further
processing by other components of the shell.
*/

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "types.h"

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
