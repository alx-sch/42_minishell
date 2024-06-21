/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:14:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/20 15:02:35 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_err_invalid_option(char *input, int i)
{
	if (input[i] == '-' && is_space(input[i - 1]))
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
		while (input[i] && !is_space(input[i]))
			write(2, &input[i++], 1);
		write(2, "': not a valid identifier\n", 27);
		return (0);
	}
	return (1);
}

int	is_export(char *input)
{
	int	i;

	i = 0;
	while (is_space(input[i]))
		i++;
	if (input[i++] != 'e')
		return (0);
	if (input[i++] != 'x')
		return (0);
	if (input[i++] != 'p')
		return (0);
	if (input[i++] != 'o')
		return (0);
	if (input[i++] != 'r')
		return (0);
	if (input[i++] != 't')
		return (0);
	if (input[i] && !is_space(input[i]))
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == '-')
			return (export_err_invalid_option(input, i));
		i++;
	}
	return (1);
}
