/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/08 17:30:22 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
main is first of all a loop that runs the shell taking inputs from the user
and executing them until the user decides to exit it.
*/
int	main(int argc, char **argv)
{
	char	*input;

	argc = 0;
	argv = NULL;
	while (1)
	{
		input = readline(PROMPT); // Display prompt and read input
		// Process input (this will be implemented later)
		if (input) // Checking if input is not NULL.
			add_history(input); // Adding to input-history.
		free(input);
	}
	exit(EXIT_SUCCESS);
}
