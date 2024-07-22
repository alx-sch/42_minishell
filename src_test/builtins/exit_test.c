/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:35:04 by natalierh         #+#    #+#             */
/*   Updated: 2024/07/22 16:08:19 by nholbroo         ###   ########.fr       */
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
		print_error_exit(data);
	exit_code = (unsigned int) ft_atoi(exit_arg); // Converting the numeral part of the string to an unsigned int.
	free_env_struct(&data->envp_temp);
	free_env_struct(&data->export_list);
	free_data(data);
	printf("exit\n"); // Prints "exit" on the STOUT.
	return (exit_code); // Returning the exit code.
}

int	is_exit(t_data *data)
{
	int	i;

	i = 0;
	while (is_whitespace(data->input[i])) // Skipping all whitespaces in the beginning
		i++;
	if (data->input[i++] != 'e') // Hard-checking for "exit".
		return (0);
	if (data->input[i++] != 'x')
		return (0);
	if (data->input[i++] != 'i')
		return (0);
	if (data->input[i++] != 't')
		return (0);
	if (data->input[i] && !is_whitespace(data->input[i]))
		return (0);
	while ((data->input[i]) && (is_whitespace(data->input[i]) 
		|| data->input[i] == '+' || data->input[i] == '-' 
		|| (data->input[i] >= '0' && data->input[i] <= '9'))) // Checking if what comes after "exit" is either numerical, '+', '-' or whitespaces. If it's not, then it's not valid.
		i++;
	exit_check_argc(data); // Checking if there are more than one argument to the "exit" command -> in that case it prints an error message and exits.
	if (data->input[i] != '\0') // If something that comes after 'exit' is not whitespace or a number, printing an error message, and exiting the process.
		print_error_exit(data);
	return (1);
}
