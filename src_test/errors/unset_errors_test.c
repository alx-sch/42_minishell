/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_errors_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:25:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/26 16:11:08 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_err_memalloc_fail(t_env **envp_temp)
{
	free_env_struct(envp_temp); // Freeing the struct.
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

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
