/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 19:45:59 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checking if the input is a builtin command, and checks if the arguments are
// valid.
int	parsing(t_data *data) // instead of input the data_struct can be passed (which contains a cd struct; initializatio for cd struct can also be added to init_data_strcut() in main.c; this helps to make cd fcts more concise)
{
	if (is_pwd(data->input)) // Checking if the input is "pwd". Ignores extra junk after pwd, like bash, but not handling options. Might implement error message with "invalid option".
		pwd(); // Calls the pwd-function that is working as the command.
	else if (is_cd(data->input)) // Checks if the input is "cd", accepts whitespaces and something following "cd" like "     cd    /home/natalierh". But not "cdd".
		cd(data->input, data->envp_temp); // Calls the cd-function that works like the command.
	else if (is_env(data->input)) //Checks if the input is "env". Ignores whitespaces before and after "env", but won't work if there are other characters present.
		env(data->envp_temp); // Calls the env-function that works like the command.
	else if (is_exit(data)) // Checks if the input is "exit". It accepts whitespaces before and after, and and exit code like "12", "+32" or "-213".
	{
		get_next_line(-1); // cleans gnl stash, if existen
		exit(exit_with_code(data)); // Exits minishell with correct exit code.
	}
	else if (is_unset(data->input)) // Checks if the input is "unset", accepts arguments, but not options.
	{
		unset(data->input, &data->envp_temp); // Unsets an environmental variable if it exists. If it doesn't, nothing happens.
		unset(data->input, &data->export_list); // Unsets an environmental variable if it exists. If it doesn't, nothing happens.
	}
	else if (is_export(data->input)) // Checks if the input is "export", accepts arguments, but no options.
		export(data); // Adds an environmental variable to the export and env list if it is assigned a value, or only to export list if it's not assigned a value. Also assigns a value a variable if it already exists.
	else if (is_echo(data->input)) // Checks if the input is "echo", accepts the option '-n', but no other options. Accepts all arguments.
		minishell_echo(data); // Outputs the input, with or without newline.
	else
		return (1);
	return (0);
}
