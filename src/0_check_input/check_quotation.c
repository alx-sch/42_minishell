/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 18:44:58 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function that checks an input string for both single and
double quotations. If a quotation is not closed, the function prints an error
message into the standard error output.
*/

#include "minishell.h"

// FUNCTION IN FILE

int	is_quotation_closed(t_data *data);

/*
Checks if the quotation mark at a given position has a corresponding closing
quotation mark and its position in the input string.

Returns:
- The position of the closing quotation mark if found.
- 0 if the closing quotation mark is not found; also prints an error message
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
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_PRE, STDERR_FILENO);
	ft_putstr_fd(char_str, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_SUF, STDERR_FILENO);
	ft_putstr_fd(i_str, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	free(i_str);
	return (0);
}

/*
Checks if the current character in the input string is a quotation mark
and if so, checks if it is properly closed.

Returns:
- 1 if no quotation mark is found or if the quotation mark is properly closed.
- 0 if a quotation mark is found but not properly closed.
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
