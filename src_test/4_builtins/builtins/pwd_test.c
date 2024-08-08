/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/07 18:26:17 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prints out the current working directory. If something goes wrong, it prints
an error message with errno set to indicate the error.
@param cwd "Current working directory"*/
int	pwd(t_exec *exec)
{
	char	cwd[4096]; // It is hardset to 4096, as it is the max amount of characters allowed in a path.

	if (exec->flags[1])
	{
		if (exec->flags[1][0] == '-')
			return (pwd_invalid_option(exec->flags[1], 0));
	}
	if (getcwd(cwd, sizeof(cwd))) // Checking that getcwd-function works. It is used to find current working directory.
		printf("%s\n", cwd); // Printing the current working directory.
	else
		print_err_msg_prefix("pwd"); // If getcwd fails, this function will print an error.
	return (0);
}
