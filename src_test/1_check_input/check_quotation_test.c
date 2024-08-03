/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/31 16:52:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains a functions to initially check the user's input:
-	Checks if input is empty (or only consists of whitespace)
-	Checks if input contains unclosed quotations and prints an error message
	and sets a custom exit code if that's the case.
*/

#include "minishell.h"

// IN FILE:

int	is_input_empty(char *input);
int	is_quotation_closed(t_data *data);

/**
Checks if the user input is empty or consists only of whitespace.

 @return `0` if the user input is not empty.
		 `1` if the user input is empty, consists only of whitespace or is NULL.
*/
int	is_input_empty(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i])
	{
		if (!is_whitespace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
Used in is_closed().

Prints an error message for unclosed quotations including the
position of the invalid synatax (position '-1' used as fallback if
ft_itoa fails). Also updates the `errno` to a custom `errno`.

 @param str_j Quotation symbol (' or ").
 @param i_str The string representation of position of piping syntax error.
*/
static void	print_open_quotation_err_msg(char *char_str, char *i_str)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO); // Set error color for the output
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_PRE, STDERR_FILENO);
	ft_putstr_fd(char_str, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_SUF, STDERR_FILENO);
	ft_putstr_fd(i_str, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
	errno = 420; // custom minishell exit status, bash would not return an error for unclosed quotations
}

/**
Checks if the quotation mark at a given position has a corresponding closing
quotation mark and its position in the input string.

 @return The position of the closing quotation mark if found (as string literal).
		 `0` if the closing quotation mark is not found; also prints an error message
*/
static int	is_closed(t_data *data, int i, const char c)
{
	char	char_str[2]; // string to hold char c and null terminator
	char	*i_str; // string to hold the position of unclosed quotation and null terminator
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
	i_str = ft_itoa(i);
	if (!i_str)
	{
		print_err_msg(ERR_MALLOC);
		print_open_quotation_err_msg(char_str, "-1");
		return (0); // Quotation mark is not closed, pos: -1
	}
	print_open_quotation_err_msg(char_str, i_str);
	free(i_str);
	return (0); // Quotation mark is not closed
}

/**
Checks if the current character in the input string is a quotation mark
and if so, checks if it is properly closed.

 @return `1` if no quotation mark is found or if the quotation mark is properly
 		 closed.
		 `0` if a quotation mark is found but not properly closed.
 */
int	is_quotation_closed(t_data *data)
{
	int	i; // Current position in input string
	int	j; // Position of the closing quotation mark

	i = 0;
	while (data->input[i])
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
