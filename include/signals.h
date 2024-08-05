/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:51:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/05 06:54:21 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
TBD
*/

#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);
void	handle_sigquit(int sig);
void	set_sig_handler(void (*handler_int)(int), void (*handler_quit)(int));

#endif
