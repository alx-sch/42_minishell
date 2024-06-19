/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/19 13:42:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			L_RED BOLD
# define ERR_MALLOC			ERR_COLOR "ERROR: malloc() failed" RESET
# define ERR_PREFIX			"minishell: "
# define ERR_REDIR_OPERAND	"syntax error after redirection "
# define ERR_NOT_CLOSED_PRE	"opening quotation "
# define ERR_NOT_CLOSED_SUF " is not closed\n"

#endif
