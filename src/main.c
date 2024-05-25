/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/25 08:40:36 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*token_list;

	argc = 0;
	argv = NULL;
	while (1)
	{
		input = readline(PROMPT);
		if (input)
			add_history(input);
		parsing(input, envp);
		free(input);
		ft_lstclear(&token_list, del_token);
	}
	exit(EXIT_SUCCESS);
}
