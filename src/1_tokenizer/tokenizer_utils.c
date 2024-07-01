/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:04:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 20:21:51 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This source file contains utility functions used in the tokenization process.
Specifically, it includes functions to identify whitespace characters and
token delimiters.
*/

#include "minishell.h"

// IN FILE:

int	is_delimiter(t_data *data, const char c);

/*
Used in is_delimiter().

Checks if a character in the input string is a quotation mark and sets
the quote state.

If no quote is currently set in the `quote` member of the `data` structure and
the input character is a single (') or double (") quotation mark, it sets the
`quote` member to that character.
If the input character matches the currently set quotation mark, it unsets
the `quote` member.
*/
static void	is_quotation(t_data *data, const char c)
{
	if (!data->quote)
	{
		if (c == '\'' || c == '\"')
			data->quote = c;
	}
	else if (c == data->quote)
		data->quote = '\0';
}

/*
Checks if a character is a delimiter during tokenization.

The function first checks if the character is a quotation mark by calling
is_quotation(), which sets or unsets the quote state in the provided `t_data`
struct. If a quote is open, delimiters are ignored (as part of quotation).

Parameters:
- t_data *data: A pointer to the `t_data` structure.
- char c: The character to check.

Returns:
- 1 if the character is a delimiter and not within a quotation.
- 0 otherwise.
*/
int	is_delimiter(t_data *data, const char c)
{
	is_quotation(data, c);
	if (!data->quote)
	{
		if (is_whitespace(c) || c == '>' || c == '<' || c == '|' || c == '\n'
			|| c == '\0')
			return (1);
	}
	return (0);
}
