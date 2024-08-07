/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:32:53 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/07 19:00:16 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The main function of the execution. Prepares for execution, executes the
program and exits.*/
void	execution(t_data *data, t_exec *exec, int position)
{
	int	builtin_exit_code;

	builtin_exit_code = 0;
	prep_execution(data, exec, position);
	if (is_builtin(exec))
	{
		builtin_exit_code = builtin(data, exec);
		free_exec(exec);
		free_data(data, 1);
		exit(builtin_exit_code);
	}
	execve(exec->current_path, exec->flags, exec->envp_temp_arr);
	exec_errors(data, exec, 4);
	exit(errno);
}
