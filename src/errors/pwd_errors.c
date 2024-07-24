/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_errors_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:56 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 19:58:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prints out an error message in case of an option, which is not a 
functionality in "pwd" of minishell*/
int	pwd_invalid_option(char *input, int i)
{
	if (input[i] == '-' && input[i + 1])
	{
		write(2, "minishell: pwd: ", 17);
		write(2, &input[i], 1);
		write(2, &input[i + 1], 1);
		write(2, ": invalid option\n", 18);
		return (0);
	}
	return (1);
}
