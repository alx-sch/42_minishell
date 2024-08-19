/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/19 15:42:36 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines error messages and formatting constants.
By centralizing error messages in one place, it provides several advantages,
e.g. consistency, easier management, clearer code structure and maintenance.
*/

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_COLOR			"\033[91m\033[1m"
# define ERR_MALLOC			"ERROR: malloc() failed"
# define ERR_GET_CWD		"ERROR: Failed to retrieve the working directory"
# define ERR_HIST_FILE		"ERROR: Unable to set the path to the history file"
# define ERR_PREFIX			"minishell: "
# define ERR_SYNTAX			"syntax error after "
# define ERR_EMPTY_PIPE		"syntax error before '|': 'missing input"
# define ERR_NOT_CLOSED_PRE	"quotation "
# define ERR_NOT_CLOSED_SUF " is not closed (position: "
# define ERR_TOKEN			"ERROR: Tokenization failed"
# define ERR_PARSE_HEREDOC 	"ERROR: Heredoc parsing failed"
# define ERR_DEL_HEREDOC	"ERROR: Failed to delete heredoc file"
# define ERR_EXP_VAR		"ERROR: Variable expansion failed"
# define ERR_TRIM_QUOTE		"ERROR: Removal of paired quotes failed"
# define ERR_GET_T_ATT		"ERROR: Failed to retrieve terminal attributes"
# define ERR_SET_T_ATT		"ERROR: Failed to set new terminal attributes"
# define WARN_EOT_HERE_1	"warning: here-document delimited by end-of-file "
# define WARN_EOT_HERE_2	"(wanted `"
# define WARN_EOT_HERE_3	"')"
#endif
