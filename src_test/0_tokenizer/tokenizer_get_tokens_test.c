/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_get_tokens_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:59:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/19 14:35:15 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
To handle memory allocation failures create_token() more efficiently, this
helper function cleans up the allocated memory outputs an error message to
the standard error stream.
*/
static void	malloc_fail_in_create_token(t_data *data)
{
	if (data->tok.tok) // Check if the token pointer within data is not NULL
	{
		if (data->tok.tok->lexeme) // If the token's lexeme has been allocated, free it and set to NULL
		{
			free(data->tok.tok->lexeme);
			data->tok.tok->lexeme = NULL;
		}
		// Free the token itself and set the pointer to NULL
		free(data->tok.tok);
		data->tok.tok = NULL;
	}
	perror(ERR_MALLOC); // Output an error message indicating a malloc failure
}

/*
Creates a new token structure and wraps it in a linked list node,
so libft functions for list manipulation can be used.
The token contains information about its type, lexeme, and position.

Parameters:
- data: Pointer to the data structure containing token-related information.
- type: The type of the token.
- lexeme: The lexeme (content) of the token.
- i: Pointer to the current index in the input string.

Returns:
- A pointer to the newly created linked list node if successful.
- NULL if memory allocation fails or if creating the linked list node fails.
*/
t_list	*create_tok(t_data *data, t_token_type type, const char *lexeme, int *i)
{
	// Allocate memory for the new token structure
	data->tok.tok = malloc(sizeof(t_token));
	if (!data->tok.tok)
	{
		perror(ERR_MALLOC);
		return (NULL);
	}
	// Write lexeme from the stack into the token structure
	data->tok.tok->lexeme = ft_strdup(lexeme);
	if (!data->tok.tok->lexeme)
	{
		malloc_fail_in_create_token(data);
		return (NULL);
	}
	// Create a new linked list node with the token as its content
	data->tok.new_node = ft_lstnew(data->tok.tok);
	if (!data->tok.new_node)
	{
		malloc_fail_in_create_token(data);
		return (NULL);
	}
	// Set token type and position
	data->tok.tok->type = type;
	data->tok.tok->position = *i;
	// Update the position pointer to the end of the lexeme
	*i = *i + ft_strlen(lexeme);
	// for TESTING ONLY
	ft_printf("Input[%d]: '%s' (token type: %d)\n", data->tok.tok->position, data->tok.tok->lexeme, data->tok.tok->type);
	return (data->tok.new_node);
}

/*
Parses the input string to extract tokens and builds a token list (t_list type).

This function iterates over the input string and extracts tokens based on
certain criteria:
- It skips leading whitespace characters.
- It checks for redirection operators and adds a tokens if found.
- It checks for the shell variable '$?' (exit status) and adds a token if found.
- It treats the remaining part of the input string as a command or pathfile and
  extracts tokens accordingly.

For each token, it creates a new token node and adds it to the token list.
If a token cannot be created due to a memory allocation failure, the function
stops processing further tokens.
*/
void	get_tokens(t_data *d)
{
	int		i;
	int		start;

	i = 0;
	while (d->input[i])
	{
		while (is_space(d->input[i])) // Skipping whitespace
			i++;
		if (!is_redirection(d, &i))
		{
			printf("I am stopping here!\n"); // FOR TESTING ONLY!
			return ;
		}
		else if (d->input[i] && !is_space(d->input[i])) // if not already at end of string: all the rest is considered a COMMAND --> which is not true, could also be a pathfile -> '/' --> bash: /: Is a directory
		{
			start = i;
			while (!is_delimiter(d, d->input[i])) // is not delimiter
				i++;
			d->tmp = ft_substr(d->input, start, i - start);
			if (d->tmp[0] != '\0') // no empty token if 'start' is a delimiter, e.g. in "hello world"'test'
			{
				d->tok.new_node = create_tok(d, NOT_OPERATOR, d->tmp, &start);
				ft_lstadd_back(&d->tok.tok_lst, d->tok.new_node);
			}
			free(d->tmp);
		}
	}
}
