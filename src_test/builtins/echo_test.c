/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:05:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/26 16:35:09 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char *input, bool print_newline)
{
	int	i;

	i = 4;
	while (input[i] && is_space(input[i]))
		i++;
	if (input[i] && input[i] == '-')
	{
		i += 2;
		while (input[i] && is_space(input[i]))
			i++;
	}
	while (input[i])
	{
		if (is_space(input[i]))
		{
			while (input[i] && is_space(input[i]))
				i++;
			if (input[i])
				write(1, " ", 1);
		}
		write(1, &input[i++], 1);
	}
	if (print_newline)
		write(1, "\n", 1);
}

int	check_option_echo(char *input)
{
	int	i;

	i = 4;
	while (input[i] && is_space(input[i]))
		i++;
	if (input[i] == '-')
		return (1);
	return (0);
}

void	minishell_echo(t_data *data)
{
 	if (check_option_echo(data->input))
		print_echo(data->input, false);
	else
		print_echo(data->input, true);
}

static int	echo_err_invalid_option(char *input, int i)
{
	if (input[i] == '-' && input[i + 1] && input[i + 1] != 'n')
	{
		write(2, "minishell: echo: invalid option: -- '", 38);
		write(2, &input[i + 1], 1);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}

int	is_echo(char *input)
{
	int	i;

	i = 0;
	while (is_space(input[i]))
		i++;
	if (input[i++] != 'e')
		return (0);
	if (input[i++] != 'c')
		return (0);
	if (input[i++] != 'h')
		return (0);
	if (input[i++] != 'o')
		return (0);
	if (input[i] && !is_space(input[i]))
		return (0);
	while (input[i] != '\0')
	{
		if (!is_space(input[i]))
			return (echo_err_invalid_option(input, i));
		i++;
	}
	return (1);
}
