/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 14:28:54 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i])) // Skipping all whitespaces
		i++;
	if (input[i++] != 'p') // Hard-checking for p
		return (0);
	if (input[i++] != 'w') // And w
		return (0);
	if (input[i++] != 'd') // And d. Returning 0 if it's not exactly "pwd".
		return (0);
	if (!input[i]) // Input is only "pwd", and is valid.
		return (1);
	if (!is_whitespace(input[i])) // If there is still more input after "pwd" and it is not a space - that would mean e.g. "pwda" instead of "pwd a", and that should not be handled, so I return 0.
		return (0);
	while (input[i] && is_whitespace(input[i])) // Moving past spaces, while there is more input after "pwd".
		i++;
	if (input[i] && input[i] == '-') // If the first encounter after "pwd" and whitespaces is a '-' sign, it is an invalid option.
			return (pwd_invalid_option(input, i));
	return (1); // If the input has ended after "pwd" - or there is more left, but it's separated by at least one space - it is valid and I return 1.
}

void	pwd(void)
{
	char	cwd[4096]; // It is hardset to 4096, as it is the max amount of characters allowed in a path.

	if (getcwd(cwd, sizeof(cwd))) // Checking that getcwd-function works. It is used to find current working directory.
		printf("%s\n", cwd); // Printing the current working directory.
	else
		perror("minishell: pwd"); // If getcwd fails, this function will print an error.
}
