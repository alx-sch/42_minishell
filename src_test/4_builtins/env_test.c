/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:38:05 by natalierh         #+#    #+#             */
/*   Updated: 2024/08/06 15:07:28 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints out a list of environment variables, sorted after "last modified".
// Acts like the "env"-command in bash.
int	env(t_exec *exec, t_env *envp_temp)
{
	if (exec->flags[1] != NULL)
	{
		env_error_messages(exec->flags[1], 0);
		return (1);
	}
	while (envp_temp)
	{
		printf("%s=%s\n", envp_temp->e_var, envp_temp->value);
		envp_temp = envp_temp->next;
	}
	return (1);
}
