/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:36:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/19 14:34:30 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION TBD
*/

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*
Data type 'enum' defines a set of constants via integer (starting with 0).
Categorizes tokens / lexemes:
-	CMD:			Command to be passed to execve()
-	BI_ECHO:		Custom function (builtint) 'echo'
-	BI_CD:			Custom function (builtint) 'cd'
-	BI_PWD:			Custom function (builtint) 'pwd'
-	BI_EXPORT:		Custom function (builtint) 'export'
-	BI_UNSET:		Custom function (builtint) 'unset'
-	BI_ENV:			Custom function (builtint) 'env'
-	BI_EXIT:		Custom function (builtint) 'exit'
-	PATH:			Path or file
-	ARG:			Arguments to command (file names, options, etc.) // NOT SURE IF REALLY NEEDED?
-	PIPE:			'|'
-	REDIRECT_IN:	'<'
-	REDIRECT_OUT:	'>'
-	APPEND_OUT:		'>>'
-	HEREDOC:		'<<'
-	HEREDOC_DELIM:	String delimiter as specified after HEREDOC input
-	DOLLAR:			Parameter extension of variables
-	EXIT_CODE:		'$?': Exit status of the most recently executed pipeline
-	EOF:			End-of-file token
*/
typedef enum e_token_type
{
	NOT_OPERATOR,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND_OUT,
	HEREDOC,
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
- int i:			Current index in the input string.
- int j:			Local index to keep track of the initial position i.
- char *tmp:		Store temporary string.
- t_token *tok:		Token structure containing lexemic information.
- t_list *new_node:	t_list node to be added to list via ft_lstadd_back().
- t_list tok_lst:	Linked list of tokens / lexemes.
*/
typedef struct s_tok
{
	t_token	*tok;
	t_list	*new_node;
	t_list	*tok_lst;
}	t_tok;

#endif
