/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/12 09:02:29 by aschenk          ###   ########.fr       */
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
	init_history();
	init_data_struct(&data, argc, argv, envp);
	while (1)
	{
		handle_signals();
		data.input = readline(PROMPT);
		if (g_signal)
			data.exit_status = EOWNERDEAD;
		g_signal = 0; // reset signal variable for heredoc prompt
		handle_signals_heredoc();
		if (data.input && !is_input_empty(data.input))
		{
			if (!is_whitespace(data.input[0]))
				add_history_to_file(data.input);
			if (is_quotation_closed(&data) && get_tokens(&data)
				&& parse_tokens(&data))
			{
				handle_signals_exec();
				set_terminal_mode(1);
				init_exec(&data);
				set_terminal_mode(0);
			}
		}
		free_data(&data, 0); // why exit status hardcoded here? In what instances are
	}
}
