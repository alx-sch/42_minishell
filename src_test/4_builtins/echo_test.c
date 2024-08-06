/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:05:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/06 16:12:18 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints whatever argument passed to "echo"-command.
//
// print_newline:
// -If true, it means echo is called with no options, and a newline should be
// printed.
// -If false, it means echo is called with "-n" option, and a newline
// should NOT be printed.
void	print_echo(t_exec *exec, bool print_newline)
{
	int	str;

	str = 2;
	if (print_newline)
		str = 1;
	while (exec->flags[str])
	{
		printf("%s", exec->flags[str++]);
		if (exec->flags[str])
			printf(" ");
	}
	if (print_newline)
		printf("\n");
}

// Works like the "echo"-command, essentially outputting whatever is passed
// as an argument to echo. The function checks if there is an "-n"-option or
// not, to see if newline should be printed or not.
int	minishell_echo(t_exec *exec)
{
	if (exec->flags[1] && !ft_strcmp(exec->flags[1], "-n"))
		print_echo(exec, false);
	else
		print_echo(exec, true);
	return (1);
}
