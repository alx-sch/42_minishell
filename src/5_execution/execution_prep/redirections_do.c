/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_do.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:19:43 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/14 12:59:24 by nholbroo         ###   ########.fr       */
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
	if (exec->redir_out || exec->append_out)
	{
		if (access(exec->outfile, F_OK == -1))
		{
			exec->outfile_fd = open(exec->outfile, O_CREAT | O_WRONLY, 0644);
			if (exec->outfile_fd == -1)
				redirections_errors(data, exec, 1, 0);
			close(exec->outfile_fd);
			exec->outfile_fd = 0;
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
	close(exec->infile_fd);
}

static void	redir_out(t_data *data, t_exec *exec)
{
	if (exec->append_out)
		exec->outfile_fd = open(exec->outfile, O_WRONLY | O_APPEND, 0644);
	else
		exec->outfile_fd = open(exec->outfile, O_WRONLY | O_TRUNC, 0644);
	if (exec->outfile_fd == -1)
		redirections_errors(data, exec, 1, 0);
	if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
		redirections_errors(data, exec, 1, 0);
	close (exec->outfile_fd);
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
	if (exec->redir_out | exec->append_out)
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
