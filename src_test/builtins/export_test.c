/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:14:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 17:14:22 by nholbroo         ###   ########.fr       */
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

void	add_env_var_only_export(t_data *data, char *arg)
{
	char	*envvar;
	t_env	*node;

	envvar = ft_strjoin("declare -x ", arg);
	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->previous = NULL;
	node->value = ft_strdup(envvar);
	free(envvar);
	node->printed = 0;
	ft_env_tmp_add_back(&data->export_list, node);
}

void	add_env_var_both(t_data *data, char *arg)
{
	t_env	*node;

	add_env_var_only_export(data, arg);
	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->previous = NULL;
	node->value = ft_strdup(arg);
	node->printed = 0;
	ft_env_tmp_add_back(&data->envp_temp, node);
}

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
	int		i;

	i = 1;
	args = ft_split(data->input, ' ');
	if (!args[1])
		print_export(data->export_list);
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
			add_env_var_only_export(data, args[i]);
		else
			add_env_var_both(data, args[i]);
		i++;
	}
	ft_freearray(args);
}

static int	export_check_option(char *input, int i)
{
	while (input[i] != '\0')
	{
		if (input[i] == '-')
			return (export_err_invalid_option(input, i));
		i++;
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
	return (export_check_option(input, i));
}
