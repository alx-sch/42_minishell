/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:51:04 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/03 09:18:17 by aschenk          ###   ########.fr       */
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
void	set_handler(void (*handler)(int));

#endif
