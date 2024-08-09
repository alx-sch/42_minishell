/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/09 21:46:49 by aschenk          ###   ########.fr       */
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
		//ft_suppress_output();
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
				init_exec(&data);
			}
			//ft_restore_output();
		}
		// Maybe as a check completely in the end, if nothing else worked, we can mimic the "Command <some_command> not found"?
		//print_token_list(data.tok.tok_lst); // TESTING ONLY
		//data.exit_status = errno; // update exit status
		//printf("after parsing -- exit status: %d\n", data.exit_status);
		//printf("TEST\n");
		ft_restore_output();
		free_data(&data, 0); // why exit status hardcoded here? In what instances are
	}
}
