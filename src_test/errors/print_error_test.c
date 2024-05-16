/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/16 11:58:29 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This function will print an error based on the error code from errno.
// I implemented "error_code" as an argument, as it has to be an argument,
// although it is not being used properly yet.

void	print_error_cd(int error_code, t_cd **cd)
{
	if (error_code == 1) // Memory allocation failure
	{
		free_cd_struct(cd);
		errno = ENOMEM;
		printf("%s\n", strerror(errno));
		exit(1);
	}
	else if (error_code == 2) // Failure with cd-command.
		printf("cd: %s\n", strerror(errno));
	else if (error_code == 3)
	{
		write(2, "test\n", 5);
		free_cd_struct(cd);
	}
}

// Maybe make a struct that contains all the error messages?
