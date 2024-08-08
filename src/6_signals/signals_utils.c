/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:30:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/08 14:31:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
