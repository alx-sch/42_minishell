/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:35 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 22:20:28 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*A part of initializing the exec struct, setting all members to NULL.*/
t_exec	*set_exec_members_to_null(t_exec *exec)
{
	exec->curr_child = 0;
	exec->count_flags = 0;
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
	exec->cmd_found = 0;
	return (exec);
}

/*Creates the necessary child processes, one per command. Creates one common
pipe for all the processes, while always saving a pointer to each side of the
pipe in a different variable. */
static void	create_child_processes(t_data *data, t_exec *exec)
{
	pid_t	pid;
	int		*stat_loc;
	t_list	*current;

	stat_loc = NULL;
	current = (t_list *)data->tok.tok_lst;
	data->tok.tok = (t_token *)current->content;
	while (exec->curr_child < data->pipe_nr + 1)
	{
		create_pipe(data, exec);
		pid = fork(); // Remember to protect!
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
	// int		i;

	// i = 0;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		exec_errors(data, exec, 1);
	exec = set_exec_members_to_null(exec);
	exec->child = malloc(sizeof(t_child));
	if (!exec->child)
		exec_errors(data, exec, 1);
	if (data->pipe_nr == 0)
		exec->child->nbr = malloc(sizeof(pid_t) * 2);
	else
		exec->child->nbr = malloc(sizeof(pid_t) * (data->pipe_nr + 2));
	if (!exec->child->nbr)
		exec_errors(data, exec, 1);
	create_child_processes(data, exec);
	free_exec(exec);
}
