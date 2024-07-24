/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/23 17:28:40 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This header file defines error messages and formatting constants.
By centralizing error messages in one place, it provides several advantages,
e.g. consistency, easier management, clearer code structure and maintenance.
*/

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			"\033[91m\033[1m"
# define ERR_MALLOC			"ERROR: malloc() failed"
# define ERR_PREFIX			"minishell: "
# define ERR_SYNTAX			"syntax error after "
# define ERR_EMPTY_PIPE		"syntax error before '|': 'missing input'"
# define ERR_NOT_CLOSED_PRE	"quotation "
# define ERR_NOT_CLOSED_SUF " is not closed (position: "

#endif
