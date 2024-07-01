/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 18:44:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			L_RED BOLD
# define ERR_MALLOC			ERR_COLOR "ERROR: malloc() failed" RESET
# define ERR_PREFIX			"minishell: "
# define ERR_SYNTAX			"syntax error after "
# define ERR_NOT_CLOSED_PRE	"quotation "
# define ERR_NOT_CLOSED_SUF " is not closed (position: "

#endif
