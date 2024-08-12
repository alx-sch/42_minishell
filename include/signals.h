/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:51:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/09 21:45:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#ifndef SIGNALS_H
# define SIGNALS_H

void	ft_suppress_output(void);
void 	ft_restore_output(void);
void 	set_terminal_mode(int suppress);

void	handle_signals(void);
void	handle_signals_heredoc(void);
void	handle_signals_exec(void);

void	set_sig_action(void (*handler_int)(int), void (*handler_quit)(int));

void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);
void	handle_sigquit(int sig);
void	set_sig_handler(void (*handler_int)(int));

#endif
