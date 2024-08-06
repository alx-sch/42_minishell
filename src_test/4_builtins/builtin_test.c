/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/06 15:33:53 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checking if the input is a builtin command, checks if the arguments are
// valid and executes the builtin.
int	builtin(t_data *data, t_exec *exec) // instead of input the data_struct can be passed (which contains a cd struct; initializatio for cd struct can also be added to init_data_strcut() in main.c; this helps to make cd fcts more concise)
{
	if (!ft_strcmp(exec->cmd, "pwd")) // Checking if the input is "pwd". Ignores extra junk after pwd, like bash, but not handling options. Might implement error message with "invalid option".
		return (pwd(exec)); // Calls the pwd-function that is working as the command.
	else if (!ft_strcmp(exec->cmd, "cd")) // Checks if the input is "cd", accepts whitespaces and something following "cd" like "     cd    /home/natalierh". But not "cdd".
		return (cd(data, exec)); // Calls the cd-function that works like the command.
	else if (!ft_strcmp(exec->cmd, "env")) //Checks if the input is "env". Ignores whitespaces before and after "env", but won't work if there are other characters present.
		return (env(exec, data->envp_temp)); // Calls the env-function that works like the command.
	else if (!ft_strcmp(exec->cmd, "exit")) // Checks if the input is "exit". It accepts whitespaces before and after, and and exit code like "12", "+32" or "-213".
	{
		get_next_line(-1); // cleans gnl stash, if exists
		exit(exit_with_code(data, exec)); // Exits minishell with correct exit code.
	}
	else if (!ft_strcmp(exec->cmd, "unset")) // Checks if the input is "unset", accepts arguments, but not options.
	{
		if (exec->flags[1] && !unset_err_invalid_option(exec->flags[1], 0))
			return (1);
		unset(exec, &data->envp_temp); // Unsets an environment variable if it exists. If it doesn't, nothing happens.
		return (unset(exec, &data->export_list)); // Unsets an environment variable if it exists. If it doesn't, nothing happens.
	}
	else if (!ft_strcmp(exec->cmd, "export")) // Checks if the input is "export", accepts arguments, but no options.
		return (export(data, exec)); // Adds an environment variable to the export and env list if it is assigned a value, or only to export list if it's not assigned a value. Also assigns a value a variable if it already exists.
	else if (!ft_strcmp(exec->cmd, "echo")) // Checks if the input is "echo", accepts the option '-n', but no other options. Accepts all arguments.
		return (minishell_echo(exec)); // Outputs the input, with or without newline.
	return (0);
}
