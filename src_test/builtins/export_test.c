/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:14:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 20:00:19 by nholbroo         ###   ########.fr       */
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

// Prints a list of the current exported environmental variables, mimicking the 
// behavior of the "export"-command in bash without arguments/options.
// It is sorted in alphabetical order.
void	print_export(t_env *export_list)
{
	while (export_list)
	{
		if (export_list->value)
			printf("declare -x %s=\"%s\"\n", export_list->e_var, \
			export_list->value);
		else
			printf("declare -x %s\n", export_list->e_var);
		export_list = export_list->next;
	}
}

/*-If input is "export" WITHOUT arguments, the function prints a list.
-If there is an argument, NOT followed by a '=' it adds an environmental
variable to export list, but without assigning a value, and not adding to
env list. E.g. "export NAME".
-If there is an argument followed by a '=' and something more, it adds an
environmental variable to BOTH export and env list. E.g. "export NAME=BRAD".*/
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
			add_env_var_no_value(data, args[i]);
		else
		{
			add_env_var_envp_with_value(data, args[i]);
			add_env_var_export_with_value(data, args[i]);
		}
		i++;
	}
	ft_freearray(args);
}

// Checking if export is followed by an option (e.g. -p), which is not accepted.
// Returns 0 if an option is found.
// Return 1 if NO option is found.
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

// Checking if input is "export".
// Returns 0 if it's not "export" (e.g. "exportt") or if it is followed by an 
// option (e.g. "export -p").
// Otherwise returns 1.
int	is_export(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
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
	if (input[i] && !is_whitespace(input[i]))
		return (0);
	return (export_check_option(input, i));
}
