/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:51:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 17:05:32 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file provides declarations for signal handling functions used in
minishell. These signals handle user interruptions and program termination:

- CTRL+C : Displays a new prompt on a new line (interruption of input).
- CTRL-D : Exits minishell.
- CTRL-\ : Does nothing / is ignored.
*/

#ifndef SIGNALS_H
# define SIGNALS_H

// 6_signals/signals_prompt.c

void	handle_signals(void);
void	handle_signals_heredoc(void);

// 6_signals/signals_execution.c

void	handle_signals_exec(void);

// 6_signals/signals_exit.c

void	process_exit_signal(t_data *data, char *str);

#endif
