/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_get_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:59:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 20:18:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file implements functions for tokenizing input strings in our minishell.
Commands, operators, and redirections are parsed into distinct tokens stored
in a linked list.
*/

#include "minishell.h"

// IN FILE:

void	get_tokens(t_data *data);
t_list	*create_tok(t_data *data, t_token_type type, const char *lexeme,
			int *i);

/*
Used in create_tok().

To handle memory allocation failures in create_token() more efficiently,
this helper function cleans up the allocated memory and outputs an error message
to the standard error stream.
*/
static void	malloc_fail_in_create_token(t_data *data)
{
	if (data->tok.tok)
	{
		if (data->tok.tok->lexeme)
		{
			free(data->tok.tok->lexeme);
			data->tok.tok->lexeme = NULL;
		}
		free(data->tok.tok);
		data->tok.tok = NULL;
	}
	perror(ERR_MALLOC);
}

/*
Creates a new token structure and stores it in a `t_list` node,
so libft functions for list manipulation can be used.
The token contains information about its type, lexeme, and position.

If the token creation is successful, the index *i is updated to point to the
position immediately after the lexeme in the input string.

Parameters:
- t_data *data:	Pointer to the data structure containing token-related info.
- t_token_type (int) type:	The type of the token.
- char *lexeme: The content of the token (substring of input string)
- int *i: Pointer to the current index in the input string.

Returns:
- A pointer to the newly created `t_list` node if successful.
- NULL if memory allocation or creating the linked list node fails.
*/
t_list	*create_tok(t_data *data, t_token_type type, const char *lexeme, int *i)
{
	data->tok.tok = malloc(sizeof(t_token));
	if (!data->tok.tok)
	{
		perror(ERR_MALLOC);
		return (NULL);
	}
	data->tok.tok->lexeme = ft_strdup(lexeme);
	if (!data->tok.tok->lexeme)
	{
		malloc_fail_in_create_token(data);
		return (NULL);
	}
	data->tok.new_node = ft_lstnew(data->tok.tok);
	if (!data->tok.new_node)
	{
		malloc_fail_in_create_token(data);
		return (NULL);
	}
	data->tok.tok->type = type;
	data->tok.tok->position = *i;
	*i = *i + ft_strlen(lexeme);
	return (data->tok.new_node);
}

/*
Used in get_tokens().

Checks if the current character in the input string is a pipe (`|`) and creates
a pipe token if it is.

Returns:
- 0 if the pipe token creation failed.
- 1 if no pipe was found or the pipe token was successfully created.
*/
// static int	is_pipe(t_data *d, int *i)
// {
// 	if (d->input[*i] == '|')
// 	{
// 		d->tok.new_node = create_tok(d, PIPE, "|", i);
// 		if (d->tok.new_node == NULL)
// 			return (0);
// 		ft_lstadd_back(&d->tok.tok_lst, d->tok.new_node);
// 	}
// 	return (1);
// }

/*
Used in get_tokens().

Extracts a token from the input string starting at position *i until a
delimiter is encountered.

Returns:
- 0 if memory allocation fails during substring creation or token node creation.
- 1 if the token is successfully added OR if no token was added as
	data->input[*i] is whitespace or is at the end of the input string.
*/
static int	add_other_token(t_data *data, int *i)
{
	int	start;

	start = *i;
	if (data->input[*i] && !is_whitespace(data->input[*i]))
	{
		while (!is_delimiter(data, data->input[*i]))
			(*i)++;
		data->tmp = ft_substr(data->input, start, (*i) - start);
		if (!data->tmp)
		{
			perror(ERR_MALLOC);
			return (0);
		}
		data->tok.new_node = create_tok(data, OTHER, data->tmp, &start);
		if (data->tok.new_node == NULL)
		{
			free(data->tmp);
			return (0);
		}
		ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node);
		free(data->tmp);
	}
	return (1);
}

/*
Parses the input string to extract tokens and builds a token list (t_list type).

This function iterates over the input string and extracts tokens based on
specific criteria:
- Skips leading whitespace characters.
- Checks for redirection operators and adds tokens if found.
- Adds a token for the pipe character `|` if found.
- Treats remaining parts of the input string as OTHER tokens.

For each token, it creates a new token node and adds it to the token list.
If a token cannot be created due to a memory allocation failure, the function
stops processing further tokens.
*/
void	get_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		while (is_whitespace(data->input[i]))
			i++;
		if (!is_redirection(data, &i))
			return ;
		else if (!is_pipe(data, &i))
			return ;
		else if (!add_other_token(data, &i))
			return ;
	}
}
