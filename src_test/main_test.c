/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/03 09:49:41 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 // Define the global variable:

volatile __sig_atomic_t	g_heredoc_mode = 0;

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

void	check_for_heredocs_s(t_data *data)
{
	int		i;
	char	*heredoc_input;
	int		fd;

	fd = get_heredoc_fd(data);
	i = 0;
	while (data->input[i])
	{	if (data->input[i] == '<' && data->input[i+1] == '<')
		{
			ft_printf(HEREDOC_P);
			heredoc_input = get_next_line(STDIN_FILENO); // interactive mode <-- ADDED TO HITSORY WHEN SIGINT!
			trim_newline(heredoc_input);
			while (g_heredoc_mode == 0 && expand_variables(&heredoc_input, data) == 1
				&& ft_strcmp(heredoc_input, "EOF") != 0)
			{
				write(fd, heredoc_input, ft_strlen(heredoc_input));
				write(fd, "\n", 1);
				free(heredoc_input);
				ft_printf(HEREDOC_P);
				heredoc_input = get_next_line(STDIN_FILENO); // interactive mode -> signal
				trim_newline(heredoc_input);
			}
			if (heredoc_input)
				free(heredoc_input);
		}
		i++;
	}
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
		printf("heredoch mode: %d, errno: %d\n", g_heredoc_mode, errno);
		set_handler(handle_sigint);
		data.input = readline(PROMPT); // interactive mode
		if (g_heredoc_mode)
			data.exit_status = EOWNERDEAD;
		g_heredoc_mode = 0;
		set_handler(handle_sigint_heredoc);
		check_for_heredocs_s(&data);
		printf("heredoch mode: %d, errno: %d\n", g_heredoc_mode, errno);
		while (g_heredoc_mode == 1) // entered when SIGINT signal received in heredoc prompt
		{
			set_handler(handle_sigint);
			data.input = readline(PROMPT);
			data.exit_status = EOWNERDEAD;
			g_heredoc_mode = 0;
			set_handler(handle_sigint_heredoc);
			check_for_heredocs_s(&data);
		}

		//printf("NON_INTERACTIVE MODE STARTING\n");
		if (data.input && !is_empty(data.input))
		{
			if (!is_whitespace(data.input[0]))
				add_history(data.input);
			if (is_quotation_closed(&data) && get_tokens(&data)
				&& parse_tokens(&data))
				{
					//printf("expanded input: %s\n", data.input);
					parsing(&data);
					//if (parsing(&data)) // Checking if the input matches any of the builtins.
						//init_exec(&data);
						//printf("EXEC\n");
				}
		}
		// Maybe as a check completely in the end, if nothing else worked, we can mimic the "Command <some_command> not found"?
		print_token_list(data.tok.tok_lst); // TESTING ONLY
		// printf("interrup status: %d\n", g_interrupted);
		free_data(&data, 0); // why exit status hardcoded here? In what instances are
		data.exit_status = errno; // update exit status
	}
}
