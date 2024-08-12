/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:33:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/12 08:52:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#include "minishell.h"
#include <termio.h>

// IN FILE:

void	handle_signals(void);
void	handle_signals_heredoc(void);
void	handle_signals_exec(void);

void set_terminal_mode(int suppress)
{
    struct termios new_settings;

    if (tcgetattr(STDIN_FILENO, &new_settings)) {
        perror("tcgetattr");
        return;
    }

    if (suppress)
        new_settings.c_lflag &= ~ECHOCTL; // Suppress control characters
    else
        new_settings.c_lflag |= ECHOCTL; // Restore default behavior


    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings))
        perror("tcsetattr");
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
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, SIG_IGN);
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
		g_signal = 1;
		write(1, "\n", STDERR_FILENO);

	}
}

void	handle_signals_exec(void)
{
	signal(SIGINT, sig_handler_exec);
	signal(SIGQUIT, SIG_IGN);
}
