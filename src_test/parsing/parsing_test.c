/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/25 16:00:02 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A temporary function for parsing, until we find a better solution.

void	parsing(t_data *data) // instead of input the data_struct can be passed (which contains a cd struct; initializatio for cd struct can also be added to init_data_strcut() in main.c; this helps to make cd fcts more concise)
{
	if (data->input)
	{
		if (is_pwd(data->input)) // Checking if the input is "pwd". Ignores extra junk after pwd, like bash, but not handling options. Might implement error message with "invalid option".
			pwd(); // Calls the pwd-function that is working as the command.
		else if (ft_strnstr(data->input, "cd", sizeof(data->input)) != NULL) // Checking if "cd" is present in the input.
			cd(data->input, data->envp);
		else if (is_env(data->input))
			env(data->envp);
		else if (is_exit(data->input)) // Checking if the input is exactly "exit"
		{
			printf("exit\n");
			exit(exit_with_code(data->input)); // Exits minishell.
		}
	}
}
