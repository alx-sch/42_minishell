/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:05:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 14:22:18 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints whatever argument passed to "echo"-command.
// 
// print_newline:
// -If true, it means echo is called with no options, and a newline should be
// printed.
// -If false, it means echo is called with "-n" option, and a newline 
// should NOT be printed.
void	print_echo(char *input, bool print_newline)
{
	int	i;

	i = 4;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (input[i] && input[i] == '-')
	{
		i += 2;
		while (input[i] && is_whitespace(input[i]))
			i++;
	}
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			while (input[i] && is_whitespace(input[i]))
				i++;
			if (input[i])
				write(1, " ", 1);
		}
		write(1, &input[i++], 1);
	}
	if (print_newline)
		write(1, "\n", 1);
}

// Checking if there is an option or not for the "echo"-command.
int	check_option_echo(char *input)
{
	int	i;

	i = 4;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (input[i] == '-')
		return (1);
	return (0);
}

// Works like the "echo"-command, essentially outputting whatever is passed
// as an argument to echo. The function checks if there is an "-n"-option or
// not, to see if newline should be printed or not.
void	minishell_echo(t_data *data)
{
	if (check_option_echo(data->input))
		print_echo(data->input, false);
	else
		print_echo(data->input, true);
}

// Checking if there is an option for the "echo"-command. If it is not '-n', it
// is not accepted, and an error message is printed.
//
// Returns 0 if there is an invalid option.
// Returns 1 upon success.
static int	echo_err_invalid_option(char *input, int i)
{
	if (input[i] == '-' && input[i + 1] && input[i + 1] != 'n')
	{
		write(2, "minishell: echo: invalid option: -- '", 38);
		write(2, &input[i + 1], 1);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}

// Checking if the input is "echo". Ignores whitespaces in beginning/end.
// Throws an error message if there is an invalid option (not -n).
// Accepts several arguments.
// 
// Returns 0 upon error.
// Returns 1 upon success.
int	is_echo(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (input[i++] != 'e')
		return (0);
	if (input[i++] != 'c')
		return (0);
	if (input[i++] != 'h')
		return (0);
	if (input[i++] != 'o')
		return (0);
	if (input[i] && !is_whitespace(input[i]))
		return (0);
	while (input[i] != '\0')
	{
		if (!is_whitespace(input[i]))
			return (echo_err_invalid_option(input, i));
		i++;
	}
	return (1);
}