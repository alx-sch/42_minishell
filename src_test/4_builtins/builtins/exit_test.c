/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:35:04 by natalierh         #+#    #+#             */
/*   Updated: 2024/08/07 18:20:54 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fun fact: *data->input is equivalent to *(data->input), not (*data)->input.

// Checks if there are multiple '+' or '-' signs in the argument of the "exit"-
//command, e.g. "exit --123".
//
// Returns 1 if there ARE multiple signs, meaning error.
// Return 0 upon success.
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

// Returns the correct exit code, indicated by the argument when "exit"-command
// is used, e.g. "exit 5".
// Using ft_atoi to convert the argument from ascii to an unsigned integer.
// Converting the "exit"-command's argument to an unsigned int, as bash doesn't 
// handle negative exit codes. 
//
// Throws an error if: there are multiple signs like "exit --123". The process
// still exits, but with a specific error code to indicate the cause of error.
// 
// Returns the defined exit code upon success, (e.g. "exit 123" will return 123
// as an unsigned int).
unsigned int	exit_with_code(t_data *data, t_exec *exec)
{
	unsigned int	exit_code;
	char			*exit_arg;

	is_exit(data, exec);
	if (exec->flags[1])
		exit_arg = exec->flags[1];
	else
	{
		free_exec(exec);
		free_data(data, 1);
		printf("exit\n");
		return (0);
	}
	if (check_multiple_signs_exit_code(exit_arg))
		print_error_exit(data, exec);
	exit_code = (unsigned int) ft_atoi(exit_arg); // Converting the numeral part of the string to an unsigned int.
	free_exec(exec);
	free_data(data, 1);
	printf("exit\n"); // Prints "exit" on the STOUT.
	return (exit_code); // Returning the exit code.
}

// Checks if the input is "exit". Ignores whitespaces in the beginning/end.
//
// Throws an error message if: there is more than one argument or if the
// argument is not numerical (e.g. "exit 23 5" or "exit abc"). It still exits,
// but with an exit code set to indicate the error.
//
// Returns 0 upon failure.
// Returns 1 upon success.
int	is_exit(t_data *data, t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->flags[1])
		return (1);
	if (exec->flags[1] && exec->flags[2])
	{
		print_err_msg_custom("exit: too many arguments", 1);
		free_exec(exec);
		free_data(data, 1);
		exit(EPERM);
	}
	while ((exec->flags[1][i]) && (is_whitespace(exec->flags[1][i]) 
		|| exec->flags[1][i] == '+' || exec->flags[1][i] == '-' 
		|| (exec->flags[1][i] >= '0' && exec->flags[1][i] <= '9'))) // Checking if what comes after "exit" is either numerical, '+', '-' or whitespaces. If it's not, then it's not valid.
		i++;
	if (exec->flags[1][i] != '\0') // If something that comes after 'exit' is not whitespace or a number, printing an error message, and exiting the process.
		print_error_exit(data, exec);
	return (1);
}
