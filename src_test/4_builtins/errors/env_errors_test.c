/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_errors_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:09:25 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 23:48:17 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints error message and exits process in the case of memory allocation
// failure for t_env struct.
void	mem_alloc_fail_env(t_env **head)
{
	free_env_struct(head);
	print_err_msg_prefix("env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

static void	print_env_err_unrecognzied(char *input, int i)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd("unrecognized option '", STDERR_FILENO);
	while (input[i] && !is_whitespace(input[i]))
		write(STDERR_FILENO, &input[i++], 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	errno = ECANCELED;
}

static void	print_env_err_invalid(char *input, int i)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd("env: invalid option: -- '", STDERR_FILENO);
	write(STDERR_FILENO, &input[i + 1], 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	errno = ECANCELED;
}

static void	print_env_err_not_exist(char *input, int i)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd("env: '", STDERR_FILENO);
	while (input[i] && !is_whitespace(input[i]))
		write(STDERR_FILENO, &input[i++], 1);
	ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	errno = EKEYEXPIRED; // it's 127 and not 2; which is weird!
}

/*Prints an error message if there is an option or argument to env command,
which is not accepted*/
int	env_error_messages(char *input, int i)
{
	if (input[i] == '-' && input[i + 1] == '-' && !is_whitespace(input[i + 2]))
		print_env_err_unrecognzied(input, i);
	else if (input[i] == '-' && !is_whitespace(input[i + 1]))
		print_env_err_invalid(input, i);
	else if (input[i] != '-' && ft_isprint(input[i]))
		print_env_err_not_exist(input, i);
	return (0);
}
