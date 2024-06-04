/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotation_test.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/04 16:51:24 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for quotations (single
and double) and creates the corresponding token if the quotation is valid.
Returns an error if the quotation is not closed.
*/

#include "minishell.h"

// FUNCTION IN FILE

int	is_quotation(t_data *data, int *i);

/*
Checks if the quotation mark at a given position has a corresponding closing
quotation mark.
Returns:
- The position of the closing quotation  mark if found.
- 0 if the closing quotation mark is not found; also prints an error message
*/
static int	is_closed(t_data *data, int *i, const char c)
{
	char	char_str[2]; // tring to hold char c and null terminator
	int		j; // Position of closing char

	j = *i + 1; // Go to position after opening char (e.g., quotation mark)
	while (data->input[j])
	{
		if (data->input[j] == c)
			return (j); // Char is closed
		j += 1;
	}
	// Error handling if closing quotation mark is not found
	char_str[0] = c;
	char_str[1] = '\0';
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_PRE, STDERR_FILENO);
	ft_putstr_fd(char_str, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_SUF, STDERR_FILENO);
	return (0); // char (e.g. quotation mark) is not closed
}

/*
Creates a 'quotation' token with the text within the closed quotation and adds
it to the token list.

Parameters:
- data: Pointer to the main data structure containing the input string.
- i: Pointer to the current position in the input string.
- type: Type of the quotation (SINGLE_QUOT or DOUBLE_QUOT).
- j: Position of the closing quotation mark.
*/
static void	create_quotation_token(t_data *data, int *i, t_token_type type,
	int j)
{
	*i = *i + 1; // Skip opening quotation mark
	data->tmp = ft_substr(data->input, *i, j - *i); // Extract text within the quotes (excluding quotes)
	data->tok.new_node = create_tok(data, type, data->tmp, i); // Create token using the extracted text
	free(data->tmp); // Free the temporary substring
	ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node); // Add the new token to the token list
	*i = *i + 1; // Move to position after the closing quotation mark
}

/*
Checks if the current character in the input string is a quotation mark
and processes it accordingly.

Parameters:
- data: Pointer to the main data structure containing the input string.
- i: Pointer to the current position in the input string.

Returns:
- 1 if no quotation mark is found or if the quotation mark is properly closed.
- 0 if a quotation mark is found but not properly closed.
 */
int	is_quotation(t_data *data, int *i)
{
	int	j;

	if (data->input[*i] == '\'') // Check for single-quotated mark
	{
		j = is_closed(data, i, '\''); // Check if it's properly closed
		if (j == 0)
			return (0); // Not closed
		else
			create_quotation_token(data, i, SINGLE_QUOT, j); // Create token for single-quoted string
	}
	else if (data->input[*i] == '\"') // Check for double-quotated mark
	{
		j = is_closed(data, i, '\"'); // Check if it's properly closed
		if (j == 0)
			return (0); // Not closed
		else
			create_quotation_token(data, i, DOUBLE_QUOT, j);  // Create token for double-quoted string
	}
	return (1); // No quotation mark found or it's properly closed
}
