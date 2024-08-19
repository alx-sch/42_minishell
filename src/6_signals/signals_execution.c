/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:41:55 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/19 20:33:47 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functionality for handling signals during command execution
within the minishell environment.

Certain commands can accept user input or run for a duration, such as 'cat',
'grep "something"', or 'sleep 5'. These commands process the EOT character
(CTRL + D) automatically in their respective ways.
*/

#include "minishell.h"

// IN FILE:

void	handle_signals_exec(void);

/**
Used in handle_signals().

Signal handler for SIGINT (CTRL + C) during execution.

 @param signum 	The signal number received (expected to be SIGINT).

It sets the global variable `g_signal` to 1 (which will set the correct exit
status)and prints a new line (to which the following prompt is displayed on).
*/
static void	sig_int_handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		printf("\n");
	}
}

/**
Used in handle_signals().

Signal handler for SIGQUIT (CTRL + \) during execution.

 @param signum 	The signal number received (expected to be SIGQUIT).

It sets the global variable `g_signal` to 1 (which will set the correct exit
status)and prints a new line (to which the following prompt is displayed on).
*/
static void	sig_quit_handler_exec(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal = 2;
		printf("Quit (core dumped)\n");
	}
}

/**
Configures signal handling during command execution.

Sets up custom signal handlers for:
 - SIGINT (CTRL+C) is handled by the `sig_handler_exec` function.
 - SIGQUIT (CTRL+\) is ignored.
*/
void	handle_signals_exec(void)
{
	signal(SIGINT, sig_int_handler_exec);
	signal(SIGQUIT, sig_quit_handler_exec);
}
