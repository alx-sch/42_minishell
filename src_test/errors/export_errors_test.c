/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errors_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:11:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 16:32:54 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Called when there is a memory allocation failure in the export command.
Cleans up memory, prints an error message and exits the process.*/
void	export_mem_alloc_failure(t_data *data)
{
	free_data(data, 1);
	errno = ENOMEM;
	perror("minishell: export");
	exit(errno);
}

/*Two different kinds of error messages for export, one in the case of 
invalid option, e.g. "export -b", and the other one in case of invalid
identifier, e.g. "export ds-d"*/
int	export_err_invalid_option(char *input, int i)
{
	if (input[i] == '-' && is_whitespace(input[i - 1]))
	{
		write(2, "minishell: export: ", 20);
		if (input[i + 1])
		{
			write(2, &input[i], 1);
			write(2, &input[i + 1], 1);
		}
		else
			write(2, &input[i], 1);
		write(2, ": invalid option\n", 18);
		return (0);
	}
	else
	{
		write(2, "minishell: export: '", 21);
		while (input[i] && !is_whitespace(input[i]))
			write(2, &input[i++], 1);
		write(2, "': not a valid identifier\n", 27);
		return (0);
	}
	return (1);
}
