/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/15 19:39:10 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
read-eval-print loop (REPL):
The shell repeatedly prompts the user for input, reads the input, evaluates it
(interprets and executes commands), and prints any output or results.
*/
static int	repl_loop(int argc, char **argv)
{
	char	*input;
	t_list	*token_list;

	(void)argc;
	(void)argv;
	input = readline(PROMPT);
	if (ft_strcmp(input, "exit") == 0) // or other signals / cmds to exit
	{
		printf("exit\n");
		free(input);
		return (1);
	}
	//tokens = parser(input);
	token_list = get_tokens(input);
	ft_lstclear(&token_list, del_token);
	free(input);
	return (0);
}

/*
main is first of all a loop that runs the shell taking inputs from the user
and executing them until the user decides to exit it.
*/
int	main(int argc, char **argv)
{
	while (1)
	{
		if (repl_loop(argc, argv))
			break ;
	}
	exit(EXIT_SUCCESS);
}
