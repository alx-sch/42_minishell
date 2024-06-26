/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/26 15:56:45 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
main is first of all a loop that runs the shell taking inputs from the user
and executing them until the user decides to exit it.
*/
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_list	*token_list;

// 	argc = 0;
// 	argv = NULL;
// 	while (1)
// 	{
// 		input = readline(PROMPT); // Display prompt and read input
// 		// Process input (this will be implemented later)
// 		if (input) // Checking if input is not NULL.
// 			add_history(input); // Adding to input-history.
// 		parsing(input, envp);
// 		token_list = get_tokens(input);
// 		free(input);
// 		ft_lstclear(&token_list, del_token);
// 	}
// 	exit(EXIT_SUCCESS);
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	print_logo();
	init_data_struct(&data, argc, argv, envp);
	while (1)
	{
		data.input = readline(PROMPT); // Display prompt and read input
		if (data.input && data.input[0] != '\0') // Checking if input is not NULL, and the input is not empty.
			add_history(data.input); // Adding to input-history.
		if (is_quotation_closed(&data)) // check if user input is valid (quotations closed, correct redirection)
		{
			//expand_variables(&data); // just testing variable expanding, will likely be used right before command exc and not here
			if (data.input && data.input[0] != '\0') // Checking if input is not NULL, and the input is not empty.
				parsing(&data); // Checking if the input matches any of the builtins.
			get_tokens(&data);
		}
		// Maybe as a check completely in the end, if nothing else worked, we can mimic the "Command <some_command> not found"?
		free_data(&data);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	d;

// 	while (1)
// 	{
// 		init_data_struct(&d, argc, argv, envp);
// 		d.tok.input = readline(PROMPT); // Display prompt and read input
// 		// Process input (this will be implemented later)
// 		if (d.tok.input ) // Checking if input is not NULL.
// 			add_history(d.tok.input); // Adding to input-history.
// 		parsing(d.tok.input, d.envp);
// 		get_tokens(d.tok.input);
// 		//free(input);
// 		free(d.tok.input);
// 		ft_lstclear(&d.tok.tok_lst, del_token);
// 	}
// 	exit(EXIT_SUCCESS);
// }
