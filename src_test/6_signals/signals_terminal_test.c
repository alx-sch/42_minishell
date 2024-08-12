/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_terminal_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:15:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/12 15:01:02 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains a function to suppress and restore the echoing of control
characters in the standard input.
*/

#include "minishell.h"

// IN FILE:

void	set_terminal_mode(int suppress);

/**
This function modifies the terminal settings for the standard input  to either
suppress or restore the display of control characters
(e.g. CTRL+C : ^C; CTRL+\ : ^\).

 @param suppress 	If non-zero, control characters will not be echoed to the
 					terminal. If zero, control characters will be echoed normally.
*/
void	set_terminal_mode(int suppress)
{
	struct termios	new_settings;

	if (tcgetattr(STDIN_FILENO, &new_settings))
	{
		print_err_msg(ERR_GET_T_ATT);
		return ;
	}
	if (suppress)
		new_settings.c_lflag &= ~ECHOCTL; // suppress control characters
	else
		new_settings.c_lflag |= ECHOCTL; // restore default behavior
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings))
		print_err_msg(ERR_GET_T_ATT);
}
