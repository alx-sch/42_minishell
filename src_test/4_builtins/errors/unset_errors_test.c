/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_errors_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:25:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/01 12:35:24 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints an error message and exits the process if there is a memory allocation
//failure in the unset command.
void	unset_err_memalloc_fail(t_env **envp_temp)
{
	free_env_struct(envp_temp); // Freeing the struct.
	print_err_msg_prefix("env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

//Prints an error message if unset is followed by an option.
int	unset_err_invalid_option(char *input, int i)
{
	if (input[i] == '-' && ft_isprint(input[i + 1])) // Checking if unset is followed by an option.
	{
		ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd("unset: invalid option: -- '", STDERR_FILENO); // Hardcode to print error, "invalid option".
		write(STDERR_FILENO, &input[i + 1], 1);
		write(STDERR_FILENO, "'\n", 2);
		ft_putstr_fd(RESET, STDERR_FILENO);
		errno = ENOENT;
		return (0);
	}
	return (1);
}
