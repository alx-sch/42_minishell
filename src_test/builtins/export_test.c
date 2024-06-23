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

// Note to self:
// When you use the export command without assigning a value, you're declaring the variable to be exported, but you're not giving it a value. 
// So, it exists, but it's empty. When you run env, it shows you all the environment variables that have been set and their values. 
// Since the variable you exported doesn't have a value, it doesn't appear in the output of env.
// On the other hand, when you use export with an assignment, you're both declaring the variable and giving it a value. So, it does appear in the output of env.
// In short, env shows variables and their values. If a variable doesn't have a value, it won't appear in the output of env, even if it has been exported.

// When you unset PATH, you're not creating a new variable or changing the value of an existing one. 
// Instead, you're removing an existing variable from the environment. 
// This action affects the current shell session and any child processes it starts after the unset command is executed. 
// The shell doesn't need to export the unset action because it directly modifies the environment of the current shell session.

// You only need to use export to:
// -> Change the value of an existing variable.
// -> Create a new variable.
// You do this in order to export the environmental variables to child processes.

void	print_export(t_env *export_list)
{
	while (export_list)
	{
		printf("%s\n", export_list->value);
		export_list = export_list->next;
	}
}

void	export(t_data *data)
{
	char	**args;

	args = ft_split(data->input, ' ');
	if (!args[1])
		print_export(data->export_list);
	ft_freearray(args);
}

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
