/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/12 11:22:42 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			"\033[31;2m\033[1m"
# define ERR_MALLOC			"\033[31;2m\033[1mERROR: malloc() failed \033[0m"
# define ERR_PREFIX			"minishell: "
# define ERR_SYNTAX			"syntax error after "
# define ERR_EMPTY_PIPE		"syntax error before '|': 'missing input'"
# define ERR_NOT_CLOSED_PRE	"quotation "
# define ERR_NOT_CLOSED_SUF " is not cloçsed (position: "

#endif
