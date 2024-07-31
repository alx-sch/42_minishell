/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_do_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:19:43 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 12:12:25 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections_errors(t_data *data, t_exec *exec, int std)
{
	ft_putstr_fd(ERR_PREFIX, 2);
	if (!std)
		ft_putstr_fd(exec->infile, 2);
	else if (std)
		ft_putstr_fd(exec->outfile, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	free_exec(exec);
	free_data(data, 1);
	exit(errno);
}

static void	check_file_exist(t_data *data, t_exec *exec)
{
	if (exec->redir_in)
	{
		if (access(exec->infile, F_OK) == -1)
			redirections_errors(data, exec, 0);
	}
	if (exec->redir_out)
	{
		if (access(exec->outfile, F_OK == -1))
		{
			if (open(exec->outfile, O_CREAT))
				redirections_errors(data, exec, 1);
		}
	}
}

void	do_redirections(t_data *data, t_exec *exec)
{
	if (exec->redir_in)
	{
		exec->infile_fd = open(exec->infile, O_RDONLY);
		if (exec->infile_fd == -1)
			redirections_errors(data, exec, 0);
	}
	if (exec->redir_out)
	{
		if (exec->append_out)
			exec->outfile_fd = open(exec->outfile, O_WRONLY | O_APPEND);
		else
			exec->outfile_fd = open(exec->outfile, O_WRONLY | O_TRUNC);
		if (exec->outfile_fd == -1)
			redirections_errors(data, exec, 1);
	}
	if (exec->redir_in)
	{
		if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
			redirections_errors(data, exec, 0);
	}
	// else if (data->pipe_no > 0)
	// {
	// 	if (dup2(exec->fd[0], STDIN_FILENO) == -1)
	// 		redirections_errors(data, exec);
	// }
	if (exec->redir_out)
	{
		if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
			redirections_errors(data, exec, 1);
	}
	// else if (data->pipe_no > 0)
	// {
	// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	// 		redirections_errors(data, exec);
	// }
	// if (close(exec->fd[0]) == -1)
	// 	redirections_errors(data, exec);
}

// if (close(pipex->fd[1]) == -1)
// 	print_error_parent(pipex, 5);

void	redirections(t_data *data, t_exec *exec)
{
	check_file_exist(data, exec);
	do_redirections(data, exec);
}
