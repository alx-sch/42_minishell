/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:33:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/02 19:05:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
• Handle ctrl-C (SIGINT), ctrl-D and ctrl-\ (SIGQUITwhich should behave like in bash.
• In interactive mode:
◦ ctrl-C (SIGINT): displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing

*/

#include "minishell.h"

/**
If SIGINT is received, the readline buffer is cleared and and new
prompt is displayed

 @param sig The received signal value
 */
void	handle_sigint(int sig)
{
	(void)sig;
	g_interrupted = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

/**
 * @brief Displays a new lines and positions the readline offset on it. If
 * SIGQUIT is received, core is dumped
 *
 * @param signum The received signal value
 */
void	display_new_line(int signum)
{
	if (signum == SIGQUIT)
		ft_printf("Quit (core dumped)");
	write(1, "\n", STDERR_FILENO);
	rl_on_new_line();
}

/**
 * @brief In interactive mode, SIGQUIT is ignored and the line is reset if
 * SIGINT is received
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
void	signals_interactive(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Out of the interactive mode, a new line is displayed after each signal
 * and core is dumped if SIGQUIT is received
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
void	signals_non_interactive(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}