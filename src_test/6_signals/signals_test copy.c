/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:33:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/09 21:15:59 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "minishell.h"
#include <termios.h>

// IN FILE:

void	handle_signals(void);
void	handle_signals_heredoc(void);
void	handle_signals_exec(void);


void ft_suppress_output(void)
{
    struct termios new_settings;

    if (tcgetattr(0, &new_settings)) // This function retrieves the current terminal attributes for the file descriptor 0 (which corresponds to the standard input, i.e., the terminal). These attributes are then stored in new_settings.
        perror("minishell: tcsetattr");
    new_settings.c_lflag &= ~ECHOCTL;
    if (tcsetattr(0, 0, &new_settings))
        perror("minishell: tcsetattr");
}

void ft_restore_output(void)
{
    struct termios original_settings;

    if (tcgetattr(STDIN_FILENO, &original_settings)) {
        perror("minishell: tcgetattr");
        return;
    }
    original_settings.c_lflag |= ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &original_settings)) {
        perror("minishell: tcsetattr");
    }
}

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

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_int);
}

static void	sig_handler_int_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	}
}

void	handle_signals_heredoc(void)
{
	signal(SIGINT, sig_handler_int_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", STDERR_FILENO);
		//rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
		ioctl(STDOUT_FILENO, TIOCSTI, "");
		// ft_printf("Quit (core dumped)");
		// write(1, "\n", STDERR_FILENO);
		// rl_on_new_line();
	}
}

void	handle_signals_exec(void)
{
	signal(SIGINT, sig_handler_exec);
	signal(SIGQUIT, sig_handler_exec);
}
