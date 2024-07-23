/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:25:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 14:28:46 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints an error message and exits the process if there is a memory allocation
//failure in the unset command.
void	unset_err_memalloc_fail(t_env **envp_temp)
{
	free_env_struct(envp_temp);
	errno = ENOMEM;
	perror("minishell: env");
	exit(errno);
}

//Prints an error message if unset is followed by an option.
int	unset_err_invalid_option(char *input, int i)
{
	if (input[i] == '-' && is_letter(input[i + 1]))
	{
		write(2, "minishell: unset: invalid option: -- '", 39);
		write(2, &input[i + 1], 1);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}
