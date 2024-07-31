/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:32:53 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 12:55:32 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The main function of the execution. Prepares for execution, executes the
program and exits.*/
void	execution(t_data *data, t_exec *exec, int position)
{
	prep_execution(data, exec, position);
	execve(exec->current_path, exec->flags, exec->envp_temp_arr);
	free_exec(exec);
	free_data(data, 1);
	exit(errno);
}
