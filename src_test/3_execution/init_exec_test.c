/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:35 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 13:45:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*A part of initializing the exec struct, setting all members to NULL.*/
t_exec	*set_exec_members_to_null(t_exec *exec)
{
	exec->curr_child = 0;
	exec->all_paths = NULL;
	exec->cmd = NULL;
	exec->current_path = NULL;
	exec->flags = NULL;
	exec->input = NULL;
	exec->child = NULL;
	exec->envp_temp_arr = NULL;
	exec->redir_in = 0;
	exec->redir_out = 0;
	exec->append_out = 0;
	exec->infile = NULL;
	exec->outfile = NULL;
	exec->first = 1;
	exec->infile_fd = 0;
	exec->outfile_fd = 1;
	return (exec);
}

static void	handle_pipe_in_parent(t_data *data, t_exec *exec)
{
	if (exec->curr_child > 0) // If this is not the first pipe, I want to close the previous pipe, as it is not needed in parent process.
	{
		close(exec->prev_pipe_fd[0]);
		close(exec->prev_pipe_fd[1]);
	}
	if (exec->curr_child < data->pipe_no) // If there are more children to come, I want to store the currrent pipe for the next child. 
	// This is in order to don't lose the data when next child is created.
	{
		exec->prev_pipe_fd[0] = exec->pipe_fd[0];
		exec->prev_pipe_fd[1] = exec->pipe_fd[1];
	}
}

static void	close_pipe_in_parent(t_data *data, t_exec *exec)
{
	if (data->pipe_no > 0) // If there was indeed an existing pipe.
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
	}
}

static void	create_pipe(t_data *data, t_exec *exec)
{
	if (exec->curr_child < data->pipe_no)
	{
		if (pipe(exec->pipe_fd) == -1)
			exec_errors(data, exec, 3);
	}
}

/*Creates the necessary child processes, one per command.*/
static void	create_child_processes(t_data *data, t_exec *exec)
{
	pid_t	pid;
	int		*stat_loc;
	t_list	*current;

	stat_loc = NULL;
	current = (t_list *)data->tok.tok_lst;
	data->tok.tok = (t_token *)current->content;
	while (exec->curr_child < data->pipe_no + 1)
	{
		create_pipe(data, exec);
		pid = fork();
		if (!pid)
			execution(data, exec, data->tok.tok->position);
		handle_pipe_in_parent(data, exec);
		exec->child->nbr[exec->curr_child++] = pid;
		while (data->tok.tok->type != PIPE && current)
		{
			current = current->next;
			if (current)
				data->tok.tok = (t_token *)current->content;
		}
		if (current && current->next)
			data->tok.tok = (t_token *)current->next->content;
	}
	close_pipe_in_parent(data, exec);
	if (waitpid(pid, stat_loc, 0) == -1)
	{
		free_exec(exec);
		free_data(data, 1);
		exit(errno);
	}
}

/*Initializes the exec struct. Allocates memory for an int array that will store
the pid's of the child processes.*/
void	init_exec(t_data *data)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		exec_errors(data, exec, 1);
	exec = set_exec_members_to_null(exec);
	exec->child = malloc(sizeof(t_child));
	if (!exec->child)
		exec_errors(data, exec, 1);
	if (data->pipe_no == 0)
		exec->child->nbr = malloc(sizeof(pid_t) * 2);
	else
		exec->child->nbr = malloc(sizeof(pid_t) * (data->pipe_no + 2));
	if (!exec->child->nbr)
		exec_errors(data, exec, 1);
	create_child_processes(data, exec);
	free_exec(exec);
}
