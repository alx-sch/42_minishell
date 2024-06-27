/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/27 19:33:42 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// FUNCTION IN FILE

void	print_heredoc_found(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;

	current_node = data->tok.tok_lst;
	while (current_node != NULL)
	{
		current_token = (t_token *)current_node->content;
		if (current_token->type == HEREDOC)
		{
			printf("HEREDOC FOUND\n");
		}
			current_node = current_node->next;
	}
}
