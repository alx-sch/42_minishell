/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/16 12:01:06 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A temporary function for parsing, until we find a better solution. 

void	parsing(char *input, char **envp)
{
	if (!ft_strcmp(input, "pwd")) // Checking if the input is exactly "pwd". NB!! Handle spaces etc.
		pwd(); // Calls the pwd-function that is working as the command.
	else if (ft_strnstr(input, "cd", sizeof(input)) != NULL) // Checking if "cd" is present in the input.
		cd(input, envp);
	else if (!ft_strcmp(input, "exit")) // Checking if the input is exactly "exit"
		exit(0); // Exits minishell.
}
