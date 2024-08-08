/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:04:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 14:02:10 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This source file contains a function to identify token delimiters.

#include "minishell.h"

// IN FILE:

int	is_delimiter(t_data *data, const char c);

/*
Used in is_delimiter().

Checks if a character in the input string is a quotation mark and sets
the quote state.

If no quote is currently set in the 'quote' member of the data structure and
the input character is a single (') or double (") quotation mark, it sets the
'quote' member to that character.
If the input character matches the currently set quotation mark, it unsets
the 'quote' member.
*/
static void	is_quotation(t_data *data, const char c)
{
	if (!data->tok.quote)
	{
		if (c == '\'' || c == '\"')
			data->tok.quote = c;
	}
	else if (c == data->tok.quote)
		data->tok.quote = '\0';
}

/**
Checks if a character is a delimiter during tokenization.

The function first checks if the character is a quotation mark by calling
is_quotation(), which sets or unsets the quote state in the provided `t_data`
struct. If a quote is open, delimiters are ignored (as part of quotation).

 @param data 	A pointer to the `t_data` structure.
 @param c 		The character to check.

 @return	`1` if the character is a delimiter and not within a quotation.
			`0` otherwise.
*/
int	is_delimiter(t_data *data, const char c)
{
	is_quotation(data, c);
	if (!data->tok.quote)
	{
		if (is_whitespace(c) || c == '>' || c == '<' || c == '|' || c == '\n'
			|| c == '\0')
			return (1);
	}
	return (0);
}
