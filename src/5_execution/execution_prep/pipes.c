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
	if (exec->curr_child > 0)
	{
		close(exec->prev_pipe_fd[0]);
		close(exec->prev_pipe_fd[1]);
	}
	if (exec->curr_child < data->pipe_nr)
	{
		exec->prev_pipe_fd[0] = exec->pipe_fd[0];
		exec->prev_pipe_fd[1] = exec->pipe_fd[1];
	}
}

void	close_pipe_in_parent(t_data *data, t_exec *exec)
{
	if (data->pipe_nr > 0)
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
	}
}
