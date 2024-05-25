/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/25 10:13:39 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd(char *input)
{
	int	i;

	i = 0;
	while (is_space(input[i])) // Skipping all whitespaces
		i++;
	if (input[i++] != 'p') // Hard-checking for p
		return (0);
	if (input[i++] != 'w') // And w
		return (0);
	if (input[i++] != 'd') // And d. Returning 0 if it's not exactly "pwd".
		return (0);
	if (!is_space(input[i]) && input[i] != '\0') // If there is still more input after "pwd" and it is not a space - that would mean e.g. "pwda" instead of "pwd a", and that should not be handled, so I return 0.
		return (0);
	return (1); // If the input has ended after "pwd" - or there is more left, but it's separated by at least one space - it is valid and I return 1.
}

void	pwd(void)
{
	char	cwd[4096]; // It is hardset to 4096, as it is the max amount of characters allowed in a path, as far as I've understood.

	if (getcwd(cwd, sizeof(cwd))) // Checking that getcwd-function works. It is used to find current working directory.
		printf("%s\n", cwd); // Printing the current working directory.
	else
		printf("pwd: %s\n", strerror(errno)); // If getcwd fails, this function will print an error.
}
