/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/13 18:40:24 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A temporary function for parsing, until we find a better solution. 

void	parsing(char *input, char **envp)
{
	if (!ft_strcmp(input, "pwd")) // Checking if the input is exactly "pwd".
		pwd(input); // Calls the pwd-function that is working as the command.
	else if (ft_strnstr(input, "cd", sizeof(input)) != NULL) // Checking if "cd" is present in the input.
		cd(input, envp);
	else if (!ft_strcmp(input, "exit")) // Checking if the input is exactly "exit"
		exit(0); // Exits minishell.
}
