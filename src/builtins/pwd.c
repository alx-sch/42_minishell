/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 14:26:29 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checking if the input is "pwd". Accepts arguments (but they won't change the
// behavior), and does NOT accept options.
int	is_pwd(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (input[i++] != 'p')
		return (0);
	if (input[i++] != 'w')
		return (0);
	if (input[i++] != 'd')
		return (0);
	if (!input[i])
		return (1);
	if (!is_whitespace(input[i]))
		return (0);
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (input[i] && input[i] == '-')
		return (pwd_invalid_option(input, i));
	return (1);
}

/*Prints out the current working directory. If something goes wrong, it prints
an error message with errno set to indicate the error.
@param cwd "Current working directory"*/
void	pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("minishell: pwd");
}
