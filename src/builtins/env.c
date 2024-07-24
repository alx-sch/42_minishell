/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:38:05 by natalierh         #+#    #+#             */
/*   Updated: 2024/07/23 13:48:08 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The env builtin - accepts several spaces etc, but not "envv" etc.
// Prints an error in the case of "env dsafgasg" or "env -dsdasf" or something.

// Checks if the input is "env". Ignores whitespaces in the beginning/end.
// Does not accept arguments or options, and will throw error messages in 
// those cases.
//
// Returns 0 if there is an error.
// Returns 1 upon success.
int	is_env(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (input[i++] != 'e')
		return (0);
	if (input[i++] != 'n')
		return (0);
	if (input[i++] != 'v')
		return (0);
	if (input[i] && !is_whitespace(input[i]))
		return (0);
	while (input[i] != '\0')
	{
		if (!is_whitespace(input[i]))
			return (env_error_messages(input, i));
		i++;
	}
	return (1);
}

// Prints out a list of environmental variables, sorted after "last modified".
// Acts like the "env"-command in bash.
void	env(t_env *envp_temp)
{
	while (envp_temp)
	{
		printf("%s=%s\n", envp_temp->e_var, envp_temp->value);
		envp_temp = envp_temp->next;
	}
}
