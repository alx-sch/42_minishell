/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_errors_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:56 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 13:13:28 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
