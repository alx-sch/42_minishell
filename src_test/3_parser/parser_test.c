/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:13:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 20:27:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// FUNCTION IN FILE

int	parse_tokens(t_data *data);

static int	expand_vars_and_trim_quotes(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	char	*trimmed_lexeme;

	current_node = data->tok.tok_lst;
	while (current_node != NULL) // traverse the token linked list
	{
		current_token = (t_token *)current_node->content;
		if (current_token->type == OTHER)
		{
			if (!expand_variables(&current_token->lexeme, data, 0)) // expand variables in the lexeme
				return (0);
			trimmed_lexeme = trim_paired_quotes(current_token->lexeme); // remove paired quotes from the lexeme
			if (!trimmed_lexeme)
				return (-1);
			free(current_token->lexeme); // free the old lexeme
			current_token->lexeme = trimmed_lexeme; // set the new lexeme
		}
		current_node = current_node->next;
	}
	return (1);
}

int	parse_tokens(t_data *data)
{
	int	return_heredocs;
	int	return_expansion_quote_trim;

	return_heredocs = process_heredocs(data);
	if (return_heredocs <= 0)
	{
		if (return_heredocs == 0) // return is '-1' if CTRL+C during heredoc prompt, don't print ERR MESSAGE then
			print_err_msg(ERR_PARSE_HEREDOC);
		return (0);
	}
	return_expansion_quote_trim = expand_vars_and_trim_quotes(data);
	if (return_expansion_quote_trim <= 0)
	{
		if (return_expansion_quote_trim == 0)
			print_err_msg(ERR_EXP_VAR);
		else
			print_err_msg(ERR_TRIM_QUOTE);
		return (0);
	}
	return (1);
}
