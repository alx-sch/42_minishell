/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_errors_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:56 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/07 18:26:09 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prints out an error message in case of an option, which is not a
functionality in "pwd" of minishell*/
int	pwd_invalid_option(char *input, int i)
{
	if (input[i] == '-' && input[i + 1])
	{
		ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		write(STDERR_FILENO, &input[i], 1);
		write(STDERR_FILENO, &input[i + 1], 1);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		errno = ENOENT;
		return (errno);
	}
	return (0);
}
