/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errors_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:11:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 12:11:44 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
