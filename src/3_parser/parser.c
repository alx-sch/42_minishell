/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:13:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/16 16:16:46 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions responsible for parsing and processing tokens
obtained from the user's input. It handles various aspects of token management
including environment variable expansion, quote trimming, and heredoc processing.
*/

#include "minishell.h"

// FUNCTION IN FILE

int	parse_tokens(t_data *data);

static int	is_empty_before_expansion(char *lexeme)
{
	char	*trimmed_lexeme;
	int		is_empty_before_var_exp;

	trimmed_lexeme = trim_paired_quotes(lexeme);
	if (!trimmed_lexeme)
		return (-1);
	if (is_empty(trimmed_lexeme) || is_only_whitespace(trimmed_lexeme))
		is_empty_before_var_exp = 1;
	else
		is_empty_before_var_exp = 0;
	free(trimmed_lexeme);
	return (is_empty_before_var_exp);
}

static int	handle_post_exp_checks(t_token *token, int was_empty_before)
{
	char	*trimmed_lexeme;

	trimmed_lexeme = trim_paired_quotes(token->lexeme);
	if (!trimmed_lexeme)
		return (-1);
	free(token->lexeme);
	token->lexeme = trimmed_lexeme;
	if (!was_empty_before && (is_empty(token->lexeme)
			|| is_only_whitespace(token->lexeme)))
		token->type = EMPTY_VAR;
	return (1);
}

/**
Expands environment variables in token lexemes and then removes paired quotes
from these lexemes.

This function traverses a linked list of tokens and performs two main operations
on lexemes of type `OTHER`:
 1.	Variable Expansion: Replaces any environment variables within the lexeme with
 	their corresponding values, respecting expansion rules within quotes.
 2.	Quote Removal: Removes paired single and double quotation characters from
 	the lexeme.

 @param data 	Pointer to the data structure containing the list of tokens and
 				environment information.

 @return		`1` if all tokens were processed successfully;
				`0` if variable expansion failed;
				`-1` if trimming paired quotes failed.
*/
static int	expand_vars_and_trim_quotes(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	int		empty_pre_exp;

	current_node = data->tok.tok_lst;
	while (current_node != NULL)
	{
		current_token = (t_token *)current_node->content;
		if (current_token->type == OTHER)
		{
			empty_pre_exp = is_empty_before_expansion(current_token->lexeme);
			if (empty_pre_exp == -1)
				return (-1);
			if (!expand_variables(&current_token->lexeme, data, 0))
				return (0);
			if (handle_post_exp_checks(current_token, empty_pre_exp) == -1)
				return (-1);
		}
		current_node = current_node->next;
	}
	return (1);
}

/**
Parses and processes tokens by handling heredoc input, expanding variables,
and trimming paired quotes. Appropriate error messages are printed if any of
these processes fail.

 @param data 	Pointer to the data structure containing the list of tokens and
				environment information.

 @return	`1` if both heredoc processing and variable expansion/quote trimming
 			succeeded;
			`0` if any operation failed.
*/
int	parse_tokens(t_data *data)
{
	int	return_heredocs;
	int	return_expansion_quote_trim;

	return_heredocs = process_heredocs(data);
	if (return_heredocs <= 0)
	{
		if (return_heredocs == 0)
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
