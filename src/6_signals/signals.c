/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:33:19 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 14:31:21 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
• Handle ctrl-C (SIGINT), ctrl-D and ctrl-\ (SIGQUITwhich should behave like in 
bash.
• In interactive mode:
◦ ctrl-C (SIGINT): displays a new prompt on a new line.
◦ ctrl-D exits the shell;  Ctrl+D doesn't send a signal directly; instead,
it affects the terminal input stream (ASCII 4 char)
◦ ctrl-\ (SIGQUIT) does nothing
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
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	set_sig_handler(void (*handler_int)(int), void (*handler_quit)(int))
{
	signal(SIGINT, handler_int);
	signal(SIGQUIT, handler_quit);
}
