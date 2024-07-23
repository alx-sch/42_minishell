/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:35:04 by natalierh         #+#    #+#             */
/*   Updated: 2024/07/23 14:23:02 by nholbroo         ###   ########.fr       */
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
unsigned int	exit_with_code(t_data *data)
{
	unsigned int	exit_code;
	char			*exit_arg;

	exit_arg = data->input;
	while (*exit_arg && (*exit_arg < '0' || *exit_arg > '9')
		&& *exit_arg != '-' && *exit_arg != '+')
		exit_arg++;
	if (check_multiple_signs_exit_code(exit_arg))
		print_error_exit(data);
	exit_code = (unsigned int) ft_atoi(exit_arg);
	free_env_struct(&data->envp_temp);
	free_env_struct(&data->export_list);
	free_data(data);
	printf("exit\n");
	return (exit_code);
}

// Checks if the input is "exit". Ignores whitespaces in the beginning/end.
//
// Throws an error message if: there is more than one argument or if the
// argument is not numerical (e.g. "exit 23 5" or "exit abc"). It still exits,
// but with an exit code set to indicate the error.
//
// Returns 0 upon failure.
// Returns 1 upon success.
int	is_exit(t_data *data)
{
	int	i;

	i = 0;
	while (is_whitespace(data->input[i]))
		i++;
	if (data->input[i++] != 'e')
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
			|| (data->input[i] >= '0' && data->input[i] <= '9')))
		i++;
	exit_check_argc(data);
	if (data->input[i] != '\0')
		print_error_exit(data);
	return (1);
}
