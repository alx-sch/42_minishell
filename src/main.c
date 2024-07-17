/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/12 20:32:04 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Used in main().

Prints a custom, color-coded logo for the minishell project.
*/
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
	printf("by Natalie Holbrook & Alex Schenk @42 Berlin, July 2024\n\n");
	printf("%s", RESET);
}

/*
Used in main().

Initializes members in the data structure to starting values.
This helps to prevent accessing uninitialized variables, particularly
in functions like free_data(), which is automatically called in case
of program termination due to an error.
*/
void	init_data_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->pipe_no = 0;
	data->envp = envp;
	//data->envp_temp = init_env_tmp(envp);
	data->input = NULL;
	data->tmp = NULL;
	data->quote = '\0';
	data->tok.tok = NULL;
	data->tok.new_node = NULL;
	data->tok.tok_lst = NULL;
}

/*
Checks if the user input is empty or consists only of whitespace.

Returns:
- 0 if the user input is not empty.
- 1 if the user input is empty, consists only of whitespace or is NULL.
*/
static int	is_input_empty(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i])
	{
		if (!is_whitespace(input[i]))
			return (0);
		i++;
	}
	return (1);
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
		data.input = readline(PROMPT);
		if (data.input && !is_input_empty(data.input))
		{
			if (!is_whitespace(data.input[0]))
				add_history(data.input);
			if (is_quotation_closed(&data))
			{
				//parsing(&data);
				get_tokens(&data);
			}
		}
		free_data(&data);
	}
}
