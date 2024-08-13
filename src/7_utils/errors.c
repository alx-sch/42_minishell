/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:15:20 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 16:50:39 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file provides functions for printing error messages with specific
formatting. These functions print errors to the standard error stream with
customizable styles and prefixes.
*/

#include "minishell.h"

// IN FILE:

void	print_err_msg(char *msg);
void	print_err_msg_prefix(char *msg);
void	print_err_msg_custom(char *msg, unsigned int print_newline);

/**
Prints an error message to the standard error stream (stderr),
with additional formatting applied.
The actual error description is obtained using `perror`, which
appends a system-generated message based on the current `errno`.

 @param msg 	The error message to be printed. This should be a
				descriptive string about the error that occurred.
*/
void	print_err_msg(char *msg)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	perror(msg);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

/**
Prints formatted error message with leading ERR_PREFIX.
The actual error description is obtained using `perror`, which
appends a system-generated message based on the current `errno`.

 @param msg 	The error message to be printed. This should be a
				descriptive string about the error that occurred.
*/
void	print_err_msg_prefix(char *msg)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	perror(msg);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

/**
Prints an error message to the standard error stream (stderr),
with additional formatting applied. Prints custom error messages
not covered by an errno, thus does not use perror().

 @param msg 			The error message to be printed. This should be a
						descriptive string about the error that occurred.
 @param print_newline 	Flag to print the newline character after
						the error message (`0` does not, otherwise does).
*/
void	print_err_msg_custom(char *msg, unsigned int print_newline)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (print_newline)
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}
