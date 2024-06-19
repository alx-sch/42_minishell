/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:04:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/19 14:36:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.
*/
int	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/*
Checks if a character in the input string is a quotation mark and toggles
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
`is_quotation`, which sets or unsets the quote state in the provided `t_data`
struct. If a quote is open, 'usual' delimiters are ignored.

Parameters:
- data: A pointer to a `t_data` structure that contains the `quote` member.
- c: The character to check.

Returns:
- 1 if the character is a delimiter and not within a quotation.
- 0 otherwise.
*/
int	is_delimiter(t_data *data, const char c)
{
	is_quotation(data, c);
	if (!data->quote) // if not within quote
	{
		if (is_space(c) || c == '>' || c == '<' || c == '|' || c == '\n'
			|| c == '\0')
			return (1);
	}
	return (0);
}

// /*
// FOR TESTING ONLY!!
// */
// void	print_token(const t_list *current)
// {
// 	t_token	*token;

// 	token = (t_token *)(current)->content;
// 	printf("token type :%u, lexeme: %s position %d", token->type, token->lexeme,
// 		token->position);
// 	return ;
// }

// /*
// FOR TESTING ONLY!!
// */
// void	print_token_list(t_list *token_list)
// {
// 	t_list	*current;

// 	current = token_list;
// 	while (current != NULL)
// 	{
// 		print_token(current);
// 		current = current->next;
// 	}
// 	return ;
// }
