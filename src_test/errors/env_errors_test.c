/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_errors_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:09:25 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 12:37:39 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mem_alloc_fail_env(t_env **head)
{
	free_env_struct(head);
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

int	env_error_messages(char *input, int i)
{
	if (input[i] == '-' && (input[i + 1]))
	{
		write(2, "env: invalid option: -- '", 25);
		write(2, &input[i + 1], 1);
		write(2, "'\n", 2);
	}
	else if (is_letter(input[i]))
	{
		errno = ENOENT;
		write(2, "env: ", 5);
		write(2, "'", 1);
		while (input[i] && !is_whitespace(input[i]))
			write(2, &input[i++], 1);
		write(2, "': ", 3);
		perror("");
	}
	return (0);
}
