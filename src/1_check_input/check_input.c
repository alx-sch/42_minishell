/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/14 13:20:21 by aschenk          ###   ########.fr       */
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

int	is_empty(char *input);
int	is_only_whitespace(char *input);
int	is_quotation_closed(t_data *data);

/**
Checks if the user input is consists only of whitespace.

 @return	`0` if the user input does not consist only of whitespace.
			`1` if the user input consists only of whitespace.
*/
int	is_only_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

/**
Checks if the user input is consists only of whitespace.

 @return	`0` if the user input is not empty.
			`1` if the user input is empty.
*/
int	is_empty(char *input)
{
	if (input[0] == '\0')
		return (1);
	return (0);
}

/**
Used in is_closed().

Prints an error message for unclosed quotations including the
position of the invalid synatax (position '-1' used as fallback if
ft_itoa fails). Also updates the `errno` to a custom `errno`.

 @param str_j 	Quotation symbol (' or ").
 @param i_str 	The string representation of position of piping syntax error.
*/
static void	print_open_quotation_err_msg(char *char_str, char *i_str,
	t_data *data)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_PRE, STDERR_FILENO);
	ft_putstr_fd(char_str, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_SUF, STDERR_FILENO);
	ft_putstr_fd(i_str, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	data->exit_status = 420;
}

/**
Checks if the quotation mark at a given position has a corresponding closing
quotation mark and its position in the input string.

 @return	The position of the closing quotation mark if found
 			(as string literal). `0` if the closing quotation mark is not
			found; also prints an error message
*/
static int	is_closed(t_data *data, int i, const char c)
{
	char	char_str[2];
	char	*i_str;
	int		j;

	j = i + 1;
	while (data->input[j])
	{
		if (data->input[j] == c)
			return (j);
		j += 1;
	}
	char_str[0] = c;
	char_str[1] = '\0';
	i_str = ft_itoa(i);
	if (!i_str)
	{
		print_err_msg(ERR_MALLOC);
		print_open_quotation_err_msg(char_str, "-1", data);
		return (0);
	}
	print_open_quotation_err_msg(char_str, i_str, data);
	free(i_str);
	return (0);
}

/**
Checks if the current character in the input string is a quotation mark
and if so, checks if it is properly closed.

 @return	`1` if no quotation mark is found or if the quotation mark
 			is properly closed.
			`0` if a quotation mark is found but not properly closed.
 */
int	is_quotation_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'')
		{
			j = is_closed(data, i, '\'');
			if (j == 0)
				return (0);
			i = j;
		}
		else if (data->input[i] == '\"')
		{
			j = is_closed(data, i, '\"');
			if (j == 0)
				return (0);
			i = j;
		}
		i++;
	}
	return (1);
}
