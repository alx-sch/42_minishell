/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/17 19:00:39 by aschenk          ###   ########.fr       */
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

void	init_data_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->tok.input = NULL;
	data->tok.tok_lst = NULL;

}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	while (1)
	{
		init_data_struct(&data, argc, argv, envp);
		data.tok.input = readline(PROMPT); // Display prompt and read input
		// Process input (this will be implemented later)
		if (data.tok.input ) // Checking if input is not NULL.
			add_history(data.tok.input ); // Adding to input-history.
		parsing(data.tok.input , envp);
		data.tok.tok_lst = get_tokens(data.tok.input);
		ft_lstclear(&data.tok.tok_lst , del_token);
	}
	exit(EXIT_SUCCESS);
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
