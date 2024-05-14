/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:36:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/14 17:24:56 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

/*
Datatype enum defines a set of constants via integer (starting with 0).
Defines lexical elements:
-	CMD:			Command
-	ARG:			Arguments to command (file names, options, etc.)
-	PIPE:			'|'
-	REDIRECT_IN:	'<'
-	REDIRECT_OUT:	'>'
-	APPEND_OUT:		'>>'
-	HEREDOC:		'<<'
-	HEREDOC_DELIM:	StringDelimiter as specified after HEREDOC input
-	EOF:			End-of-file token
*/
typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND_OUT,
	HEREDOC,
	HEREDOC_DELIM,
	EOF
}		t_token_type;

/*
TBD
*/
typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	int				position;
}	t_token;

/*
Data structure as used in scanner.c
*/
typedef struct s_scan_data
{
	int		i;
	char	*tmp;
	t_list	**print_token_list;
	t_list	*token;
}	t_scan_data;

#endif
