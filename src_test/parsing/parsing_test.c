/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/21 15:55:14 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A temporary function for parsing, until we find a better solution.

void	parsing(t_data *data) // instead of input the data_struct can be passed (which contains a cd struct; initializatio for cd struct can also be added to init_data_strcut() in main.c; this helps to make cd fcts more concise)
{
	if (is_pwd(data->input)) // Checking if the input is "pwd". Ignores extra junk after pwd, like bash, but not handling options. Might implement error message with "invalid option".
		pwd(); // Calls the pwd-function that is working as the command.
	else if (is_cd(data->input)) // Checks if the input is "cd", accepts whitespaces and something following "cd" like "     cd    /home/natalierh". But not "cdd".
		cd(data->input, data->envp); // Calls the cd-function that works like the command.
	else if (is_env(data->input)) //Checks if the input is "env". Ignores whitespaces before and after "env", but won't work if there are other characters present.
		env(data->envp_temp); // Calls the env-function that works like the command.
	else if (is_exit(data->input)) // Checks if the input is "exit". It accepts whitespaces before and after, and and exit code like "12", "+32" or "-213".
	{
		printf("exit\n"); // Prints "exit" on the STOUT.
		exit(exit_with_code(data)); // Exits minishell with correct exit code.
	}
	else if (is_unset(data->input)) // Checks if the input is "unset", accepts arguments, but not options.
		unset(data->input, &data->envp_temp); // Unsets an environmental variable if it exists. If it doesn't, nothing happens.
	else if (is_export(data->input))
		export(data);
}
