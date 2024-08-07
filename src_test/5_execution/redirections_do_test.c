/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_do_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:19:43 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/06 16:34:31 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file_exist_child(t_data *data, t_exec *exec)
{
	if (exec->redir_in)
	{
		if (access(exec->infile, F_OK) == -1)
			redirections_errors(data, exec, 0, 0);
	}
	if (exec->redir_out)
	{
		if (access(exec->outfile, F_OK == -1))
		{
			if (open(exec->outfile, O_CREAT) == -1)
				redirections_errors(data, exec, 1, 0);
		}
	}
}

static void	redir_in(t_data *data, t_exec *exec)
{
	exec->infile_fd = open(exec->infile, O_RDONLY);
	if (exec->infile_fd == -1)
		redirections_errors(data, exec, 0, 0);
	if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
		redirections_errors(data, exec, 0, 0);
}

static void	redir_out(t_data *data, t_exec *exec)
{
	if (exec->append_out)
		exec->outfile_fd = open(exec->outfile, O_WRONLY | O_APPEND);
	else
		exec->outfile_fd = open(exec->outfile, O_WRONLY | O_TRUNC);
	if (exec->outfile_fd == -1)
		redirections_errors(data, exec, 1, 0);
	if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
		redirections_errors(data, exec, 1, 0);
}

void	do_redirections(t_data *data, t_exec *exec)
{
	if (exec->redir_in)
		redir_in(data, exec);
	else if (exec->curr_child > 0)
	{
		if (dup2(exec->prev_pipe_fd[0], STDIN_FILENO) == -1)
			redirections_errors(data, exec, 0, 0);
	}
	if (exec->redir_out)
		redir_out(data, exec);
	else if (exec->curr_child < data->pipe_nr)
	{
		if (dup2(exec->pipe_fd[1], STDOUT_FILENO) == -1)
			redirections_errors(data, exec, 1, 0);
	}
	if (exec->curr_child > 0)
	{
		close(exec->prev_pipe_fd[0]);
		close(exec->prev_pipe_fd[1]);
	}
	if (exec->curr_child < data->pipe_nr)
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
	}
}

void	redirections(t_data *data, t_exec *exec)
{
	check_file_exist_child(data, exec);
	do_redirections(data, exec);
}
