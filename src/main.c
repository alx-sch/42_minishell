/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 16:37:51 by nholbroo         ###   ########.fr       */
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

	init_history();
	print_logo();
	init_data_struct(&data, argc, argv, envp);
	while (1)
	{
		set_sig_handler(handle_sigint, handle_sigquit);
		data.input = readline(PROMPT);
		if (g_signal)
			data.exit_status = EOWNERDEAD;
		g_signal = 0;
		set_sig_handler(handle_sigint_heredoc, handle_sigquit);
		if (data.input && !is_input_empty(data.input))
		{
			if (!is_whitespace(data.input[0]))
				add_history_to_file(data.input);
			if (is_quotation_closed(&data) && get_tokens(&data)
				&& parse_tokens(&data))
				init_exec(&data);
		}
		free_data(&data, 0);
	}
}
