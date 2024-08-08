/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:33:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 15:03:06 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
• Handle ctrl-C (SIGINT), ctrl-D and ctrl-\ (SIGQUITwhich should behave like in bash.
• In interactive mode:
◦ ctrl-C (SIGINT): displays a new prompt on a new line.
◦ ctrl-D exits the shell;  Ctrl+D doesn't send a signal directly; instead,
it affects the terminal input stream (ASCII 4 char)
◦ ctrl-\ (SIGQUIT) does nothing

int main()
{
    // Set up signal handler
    struct sigaction sa;
    sa.sa_handler = handle_sigint_heredoc;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // Handle input
    handle_input();

    return 0;
}
*/


#include "minishell.h"
#include <sys/ioctl.h> // Include this header for ioctl and TIOCSTI

/**
If SIGINT is received, the readline buffer is cleared and and new
prompt is displayed

 @param sig The received signal value
 */
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = 1;
	rl_replace_line("", 0); // Clear current line
	printf("\n"); // Print a newline
	rl_on_new_line(); // Move to new line
	rl_redisplay(); // Refresh the prompt
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n"); // simulates user input of pressing enter
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	set_sig_handler(void (*handler_int)(int), void (*handler_quit)(int))
{
	signal(SIGINT, handler_int); // CTRL + C
	signal(SIGQUIT, handler_quit); // CTRL + '\'
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
