/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 17:17:10 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Define the global variable:

volatile __sig_atomic_t	g_signal = 0;

// Prints a custom, color-coded logo for the minishell project.
static void	print_logo(void)
{
	printf("%s%s _  _   ", BOLD, L_RED);
	printf("%s__   %s__ _   ", ORANGE, YELLOW);
	printf("%s__   %s____   ", GREEN, BLUE);
	printf("%s_  _   %s____   ", VIOLET, L_RED);
	printf("%s__     %s__   \n", ORANGE, YELLOW);
	printf("%s( \\/ ) %s(  ) ", L_RED, ORANGE);
	printf("%s(  ( \\ %s(  ) ", YELLOW, GREEN);
	printf("%s/ ___) %s/ )( \\ ", BLUE, VIOLET);
	printf("%s(  __) %s(  )   ", L_RED, ORANGE);
	printf("%s(  )  \n", YELLOW);
	printf("%s/ \\/ \\  %s)(  ", L_RED, ORANGE);
	printf("%s/    /  %s)(  ", YELLOW, GREEN);
	printf("%s\\___ \\ %s) __ (  ", BLUE, VIOLET);
	printf("%s) _)  %s/ (_/\\ ", L_RED, ORANGE);
	printf("%s/ (_/\\ \n", YELLOW);
	printf("%s\\_)(_/ %s(__) ", L_RED, ORANGE);
	printf("%s\\_)__) %s(__) ", YELLOW, GREEN);
	printf("%s(____/ %s\\_)(_/ ", BLUE, VIOLET);
	printf("%s(____) %s\\____/ ", L_RED, ORANGE);
	printf("%s\\____/\n\n", YELLOW);
	printf("%s%s", RESET, BOLD);
	printf("by Natalie Holbrook & Alex Schenk @42 Berlin, August 2024\n\n");
	printf("%s", RESET);
}

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
		set_sig_handler(handle_sigint, handle_sigquit);
		data.input = readline(PROMPT);
		if (g_signal)
			data.exit_status = EOWNERDEAD;
		g_signal = 0; // reset signal variable for heredoc prompt
		set_sig_handler(handle_sigint_heredoc, handle_sigquit);
		if (data.input && !is_input_empty(data.input))
		{
			if (!is_whitespace(data.input[0]))
				add_history(data.input);
			if (is_quotation_closed(&data) && get_tokens(&data)
				&& parse_tokens(&data))
				{
					//printf("expanded input: %s\n", data.input);
					//printf("before parsing -- exit status: %d\n", data.exit_status);
					//parsing(&data);
					//if (parsing(&data)) // Checking if the input matches any of the builtins.
						init_exec(&data);
						//printf("EXEC\n");
				}
		}
		// Maybe as a check completely in the end, if nothing else worked, we can mimic the "Command <some_command> not found"?
		//print_token_list(data.tok.tok_lst); // TESTING ONLY
		//data.exit_status = errno; // update exit status
		//printf("after parsing -- exit status: %d\n", data.exit_status);
		free_data(&data, 0); // why exit status hardcoded here? In what instances are
	}
}
