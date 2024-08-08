/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:05:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 15:00:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "minishell.h"

// IN FILE:

bool	process_quote(char ch, bool *in_single_quote, bool *in_double_quote);
char	*trim_paired_quotes(const char *str);
int		is_variable(char *str, int i);

/**
Toggles the state of quote flags based on the current character.
If the character is a single quote (`'`) and not within a double quote,
it toggles the `in_single_quote` flag. If the character is a double quote (`"`)
and not within a single quote, it toggles the `in_double_quote` flag.

 @param ch 					The current character being processed.
 @param in_single_quote 	Flag indicating if single quotes are active.
 @param in_double_quote 	Flag indicating if double quotes are active.

 @return 					`true` if the character is a quote that is paired;
 							`false` otherwise.
*/
bool	process_quote(char ch, bool *in_single_quote, bool *in_double_quote)
{
	if (ch == '\'' && !*in_double_quote) // char is ' and not in double quote
	{
		*in_single_quote = !*in_single_quote;
		return (true);
	}
	if (ch == '"' && !*in_single_quote) // char is " and not in single quote
	{
		*in_double_quote = !*in_double_quote;
		return (true);
	}
	return (false);
}

/**
Processes a string by removing paired single and double quotation characters.
Nested quote characters are preserved.

 @param str 	The original delimiter string, which may include paired quotes.

 @return 	A newly allocated string with all paired quotes removed.
			Returns `NULL` if memory allocation fails.
*/
char	*trim_paired_quotes(const char *str)
{
	char	*trimmed_str;
	int		i;
	int		trimmed_i;
	bool	in_single_quote;
	bool	in_double_quote;

	trimmed_str = malloc(sizeof(char)*(ft_strlen(str) + 1)); // trimmed_str cannot be larger than the original str
	if (!trimmed_str)
		return (NULL);
	i = 0;
	trimmed_i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (str[i])
	{
		if (process_quote(str[i], &in_single_quote, &in_double_quote))
			i++; // skip the paired quotation char
		else
			trimmed_str[trimmed_i++] = str[i++]; // copy all but paired quotation chars
	}
	trimmed_str[trimmed_i] = '\0'; // null-terminate the trimmed string
	return (trimmed_str);
}

/**
Checks if a valid variable is encountered at position `i` in the string `str`.
A valid variable is identified by a '$' character that is followed by at least
one alphanumerical character or '?' (special variable '$?': exit status).

 @return	`1` if a valid variable is encountered.
			`0` if no valid variable is encountered.
*/
int	is_variable(char *str, int i)
{
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		return (1);
	else
		return (0);
}
