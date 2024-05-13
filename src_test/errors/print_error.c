/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/13 17:38:47 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This function will print an error based on the error code from errno.
// I implemented "error_code" as an argument, as it has to be an argument,
// although it is not being used properly yet.

void	print_error(int error_code)
{
	if (error_code == 1) // Memory allocation failure
	{
		errno = ENOMEM;
		printf("%s\n", strerror(errno));
	}
	else if (error_code == 2) // Failure with cd-command.
		printf("cd: %s\n", strerror(errno));
	else if (error_code == 3)
		strerror(errno);
}
