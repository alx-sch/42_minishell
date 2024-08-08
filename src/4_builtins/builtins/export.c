/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:14:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/08 14:16:25 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints a list of the current exported environmental variables, mimicking the
// behavior of the "export"-command in bash without arguments/options.
// It is sorted in alphabetical order.
int	print_export(t_env *export_list)
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
	return (0);
}

/*-If input is "export" WITHOUT arguments, the function prints a list.
-If there is an argument, NOT followed by a '=' it adds an environmental
variable to export list, but without assigning a value, and not adding to
env list. E.g. "export NAME".
-If there is an argument followed by a '=' and something more, it adds an
environmental variable to BOTH export and env list. E.g. "export NAME=BRAD".*/
int	export(t_data *data, t_exec *exec)
{
	int		i;

	i = 1;
	if (!exec->flags[1])
		return (print_export(data->export_list));
	if (ft_strchr(exec->flags[1], '-') || !ft_is_alphanumerical(exec->flags))
		return (export_err_invalid_option(exec->flags[1], 0));
	while (exec->flags[i])
	{
		if (!ft_strchr(exec->flags[i], '='))
			add_env_var_no_value(data, exec->flags[i]);
		else
		{
			add_env_var_envp_with_value(data, exec->flags[i]);
			add_env_var_export_with_value(data, exec->flags[i]);
		}
		i++;
	}
	return (0);
}
