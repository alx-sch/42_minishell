/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_prompts_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:33:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/12 17:19:56 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains the signal handling for the minishell and heredoc prompt.
*/

#include "minishell.h"

// IN FILE:

void	handle_signals(void);
void	handle_signals_heredoc(void);

/**
Used in handle_signals().

Signal handler for SIGINT (CTRL+C) during minishell prompt.

 @param signum 	The signal number received (expected to be SIGINT).

It sets the global variable `g_signal` to 1 (which will set the correct exit
status) prints a newline to the console, and then uses readline library functions
to replace the current input line with an empty string, move to a new line, and
edisplay the updated input.
*/
static void	sig_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
Configures signal handling during the minishell prompt.

Sets up custom signal handlers for:
 - SIGINT (CTRL+C) is handled by the `sig_handler_int` function.
 - SIGQUIT (CTRL+\) is ignored.
*/
void	handle_signals(void)
{
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, SIG_IGN);
}

/**
Used in handle_signals().

Signal handler for SIGINT (CTRL+C) during heredoc prompt.

 @param signum 	The signal number received (expected to be SIGINT).

It sets the global variable `g_signal` to 1 (which will set the correct exit
status) and simulates a pressing of `ENTER` by injecting a newline character
into the terminal's input buffer. This effectively terminates the heredoc input
by providing an end-of-input signal to the program.
*/
static void	sig_handler_int_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	}
}

/**
Configures signal handling during the heredoc prompt.

Sets up custom signal handlers for:
 - SIGINT (CTRL+C) is handled by the `sig_handler_int_heredoc` function.
 - SIGQUIT (CTRL+\) is ignored.
*/
void	handle_signals_heredoc(void)
{
	signal(SIGINT, sig_handler_int_heredoc);
	signal(SIGQUIT, SIG_IGN);
}