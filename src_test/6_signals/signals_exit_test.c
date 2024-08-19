/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exit_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:31:11 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/19 15:19:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains the handling of the CTRL+D input event.

CTRL+D does not generate a traditional signal but sends an End-Of-Transmission
(EOT) character (ASCII value 4) to the standard input. When the EOT character
is encountered, functions like `readline()` interpret this as the end of input
and will return NULL.
*/

#include "minishell.h"

// IN FILE:

void	process_exit_signal(t_data *data, char *str);

/**
Handles cleanup and program termination in response to the CTRL+D exit signal.
 @param data 	A pointer to a data structure, which will be cleaned up.
 @param str 	A pointer to a dynamically allocated string or buffer to be freed.
 				This parameter can be `NULL` if there is no allocated memory
				to free.
*/
void	process_exit_signal(t_data *data, char *str)
{
	printf("exit\n");
	cleanup(data, 1);
	if (str)
		free(str);
	exit(0);
}

/**
Handles cleanup and program termination in response to the CTRL+D exit signal.
 @param data 	A pointer to a data structure, which will be cleaned up.
 @param str 	A pointer to a dynamically allocated string or buffer to be freed.
 				This parameter can be `NULL` if there is no allocated memory
				to free.
*/
void	process_exit_signal_heredoc(t_data *data, char *str)
{
	print_err_msg_prefix(WAR_SIGQUIT_HERE_1);
	print_err_msg(WAR_SIGQUIT_HERE_2);
	ft_putstr_fd("\n", STDERR_FILENO);
	cleanup(data, 1);
	if (str)
		free(str);
	exit(0);
}
