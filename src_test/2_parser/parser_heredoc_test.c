/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 17:29:50 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// FUNCTION IN FILE

static void	count_pipes(t_data *data, t_token *node)
{
	//printf("token type: %d\n", node->type);
	if (node->type == PIPE)
		data->pipe_no += 1;
}

void	print_heredoc_found(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	char	*input_line;

	current_node = data->tok.tok_lst;
	while (current_node != NULL)
	{
		current_token = (t_token *)current_node->content;
		count_pipes(data, current_token);
		if (current_token->type == HEREDOC)
		{
			ft_printf("> "); // weirdly enough, printf() 'lags' here, thus ft_printf() is used
			input_line = get_next_line(0);	// Use get_next_line to read input from stdin (fd = 0)
			if (input_line != NULL)
			{
				printf("You entered: %s", input_line);
				free(input_line);
			}
		}
		current_node = current_node->next;
	}
	get_next_line(-1);
	printf("number of pipes found: %d\n", data->pipe_no);
}
