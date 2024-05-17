/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/17 16:30:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
