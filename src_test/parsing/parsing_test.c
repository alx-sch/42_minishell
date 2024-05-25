/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/25 10:13:57 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A temporary function for parsing, until we find a better solution.

void	parsing(char *input, char **envp) // instead of input the data_struct can be passed (which contains a cd struct; initializatio for cd struct can also be added to init_data_strcut() in main.c; this helps to make cd fcts more concise)
{
	if (is_pwd(input)) // Checking if the input is exactly "pwd". Ignores extra junk after pwd, like bash, but not handling options. Might implement error message with "invalid option".
		pwd(); // Calls the pwd-function that is working as the command.
	else if (ft_strnstr(input, "cd", sizeof(input)) != NULL) // Checking if "cd" is present in the input.
		cd(input, envp);
	else if (!ft_strcmp(input, "exit")) // Checking if the input is exactly "exit"
		exit(0); // Exits minishell.
}
