/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/17 16:31:02 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	cwd[4096]; // It is hardset to 4096, as it is the max amount of characters allowed in a path, as far as I've understood.

	if (getcwd(cwd, sizeof(cwd))) // Checking that getcwd-function works. It is used to find current working directory.
		printf("%s\n", cwd); // Printing the current working directory.
	else
		printf("pwd: %s\n", strerror(errno)); // If getcwd fails, this function will print an error.
}