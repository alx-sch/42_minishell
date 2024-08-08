/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:13:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 14:29:39 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// FUNCTION IN FILE

int	parse_tokens(t_data *data);

int	process_var_expansion(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;

	current_node = data->tok.tok_lst;
	while (current_node != NULL)
	{
		current_token = (t_token *)current_node->content;
		if (current_token->type == OTHER)
			expand_variables(&current_token->lexeme, data);
		current_node = current_node->next;
	}
	return (1);
}

int	parse_tokens(t_data *data)
{
	int	return_process_heredocs;

	return_process_heredocs = process_heredocs(data);
	if (return_process_heredocs <= 0)
	{
		if (return_process_heredocs == 0)
			print_err_msg(ERR_PARSE_HEREDOC);
		return (0);
	}
	if (!process_var_expansion(data))
	{
		print_err_msg(ERR_VAR_EXP);
		return (0);
	}
	return (1);
}
