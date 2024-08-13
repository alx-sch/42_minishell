/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:58:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/13 15:26:42 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_data *data, t_exec *exec)
{
	if (exec->curr_child < data->pipe_nr)
	{
		if (pipe(exec->pipe_fd) == -1)
			exec_errors(data, exec, 3);
	}
}

void	handle_pipe_in_parent(t_data *data, t_exec *exec)
{
	if (exec->curr_child > 0) // If this is not the first pipe, I want to close the previous pipe, as it is not needed in parent process.
	{
		close(exec->prev_pipe_fd[0]);
		close(exec->prev_pipe_fd[1]);
	}
	if (exec->curr_child < data->pipe_nr) // If there are more children to come, I want to store the currrent pipe for the next child. 
	// This is in order to don't lose the data when next child process is happening.
	{
		exec->prev_pipe_fd[0] = exec->pipe_fd[0];
		exec->prev_pipe_fd[1] = exec->pipe_fd[1];
	}
}

void	close_pipe_in_parent(t_data *data, t_exec *exec)
{
	if (data->pipe_nr > 0) // If there was indeed an existing pipe in the full input.
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
	}
}
