/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/16 16:18:03 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Define the global variable:

volatile __sig_atomic_t	g_signal = 0;


// static void	print_token_list(t_list *lst)
// {
// 	t_token	*token;

// 	while (lst)
// 	{
// 		token = lst->content;
// 		printf("Position[%d]: '%s' (token type: %d)\n", token->position,
// 			token->lexeme, token->type);
// 		lst = lst->next;
// 	}
// }


/*
main is first of all a loop that runs the shell taking inputs from the user
and executing them until the user decides to exit it.
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	print_logo();
	init_data_struct(&data, argc, argv, envp);
	while (1)
	{
		handle_signals();
		minishell_prompt(&data);
		if (g_signal)
			data.exit_status = EOWNERDEAD;
		g_signal = 0;
		handle_signals_heredoc();
		if (data.input && !is_empty(data.input))
		{
			add_history_to_file(data.input, data.path_to_hist_file);
			if (!is_only_whitespace(data.input) && is_quotation_closed(&data)
				&& get_tokens(&data) && parse_tokens(&data))
			{
				//print_token_list(data.tok.tok_lst);
				handle_signals_exec();
				init_exec(&data);
			}
		}
		cleanup(&data, 0);
	}
}
