/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/19 13:28:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function that checks an input string for both single and
double quotations. If a quotation is not closed, the function returns an error.
*/

#include "minishell.h"

// FUNCTION IN FILE


/*
Checks if the quotation mark at a given position has a corresponding closing
quotation mark.
Returns:
- The position of the closing quotation  mark if found.
- 0 if the closing quotation mark is not found; also prints an error message
*/
static int	is_closed(t_data *data, int i, const char c)
{
	char	char_str[2]; // string to hold char c and null terminator
	int		j; // Position of closing char

	j = i + 1; // Go to position after opening char (e.g., quotation mark)
	while (data->input[j])
	{
		if (data->input[j] == c)
			return (j); // Char is closed
		j += 1;
	}
	// Error handling if closing quotation mark is not found
	char_str[0] = c;
	char_str[1] = '\0';
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_PRE, STDERR_FILENO);
	ft_putstr_fd(char_str, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_SUF, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (0); // char (e.g. quotation mark) is not closed
}

/*
Checks if the current character in the input string is a quotation mark
and if so, checks if it is properly closed.

Parameters:
- data: Pointer to the main data structure containing the input string.

Returns:
- 1 if no quotation mark is found or if the quotation mark is properly closed.
- 0 if a quotation mark is found but not properly closed.
 */
int	is_quotation_closed(t_data *data)
{
	int	i; // Current position in input string
	int	j; // Position of the closing quotation mark

	i = 0;
	while(data->input[i])
	{
		if (data->input[i] == '\'') // Check for single-quotated mark
		{
			j = is_closed(data, i, '\''); // Check if it's properly closed
			if (j == 0)
				return (0); // Not closed
			i = j; // Move to the position of the closing quote
		}
		else if (data->input[i] == '\"') // Check for double-quotated mark
		{
			j = is_closed(data, i, '\"'); // Check if it's properly closed
			if (j == 0)
				return (0); // Not closed
			i = j; // Move to the position of the closing quote
		}
		i++;
	}
	return (1); // No quotation mark found or it's properly closed
}
