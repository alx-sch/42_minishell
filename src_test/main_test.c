/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 17:19:18 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Define the global variable:

volatile __sig_atomic_t	g_signal = 0;

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
		if (g_signal) // CTRL+C was received in minishell or heredoc prompt
			data.exit_status = EOWNERDEAD;
		g_signal = 0; // reset signal variable for heredoc prompt
		handle_signals_heredoc();
		if (data.input && !is_input_empty(data.input))
		{
			if (!is_whitespace(data.input[0]))
				add_history_to_file(data.input, data.path_to_hist_file);
			if (is_quotation_closed(&data) && get_tokens(&data)
				&& parse_tokens(&data))
			{
				print_token_list(data.tok.tok_lst);
				handle_signals_exec();
				init_exec(&data);
			}
		}
		free_data(&data, 0);
	}
}
