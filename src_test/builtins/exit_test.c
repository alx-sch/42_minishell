/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:35:04 by natalierh         #+#    #+#             */
/*   Updated: 2024/06/24 14:28:57 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fun fact: *data->input is equivalent to *(data->input), not (*data)->input.

static int	check_multiple_signs_exit_code(char *exit_arg)
{
	if (*exit_arg == '-' || *exit_arg == '+') 
	{
		exit_arg++;
		if (*exit_arg && (*exit_arg < '0' || *exit_arg > '9'))
			return (1);
	}
	return (0);
}

unsigned int	exit_with_code(t_data *data)
{
	unsigned int	exit_code;
	char			*exit_arg;

	exit_arg = data->input;
	while (*exit_arg && (*exit_arg < '0' || *exit_arg > '9') // This loop is skipping the input string until the exit number is getting defined. E.g. "exit     -123".
		&& *exit_arg != '-' && *exit_arg != '+')
		exit_arg++;
	if (check_multiple_signs_exit_code(exit_arg))
		print_error_exit(data->input);
	exit_code = (unsigned int) ft_atoi(exit_arg); // Converting the numeral part of the string to an unsigned int.
	free_env_struct(&data->envp_temp);
	free_env_struct(&data->export_list);
	free_data(data);
	printf("exit\n"); // Prints "exit" on the STOUT.
	return (exit_code); // Returning the exit code.
}

int	is_exit(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i])) // Skipping all whitespaces in the beginning
		i++;
	if (input[i++] != 'e') // Hard-checking for "exit".
		return (0);
	if (input[i++] != 'x')
		return (0);
	if (input[i++] != 'i')
		return (0);
	if (input[i++] != 't')
		return (0);
	if (input[i] && !is_whitespace(input[i]))
		return (0);
	while ((input[i]) && (is_whitespace(input[i]) 
		|| input[i] == '+' || input[i] == '-' 
		|| (input[i] >= '0' && input[i] <= '9'))) // Checking if what comes after "exit" is either numerical, '+', '-' or whitespaces. If it's not, then it's not valid.
		i++;
	exit_check_argc(input); // Checking if there are more than one argument to the "exit" command -> in that case it prints an error message and exits.
	if (input[i] != '\0') // If something that comes after 'exit' is not whitespace or a number, printing an error message, and exiting the process.
		print_error_exit(input);
	return (1);
}
