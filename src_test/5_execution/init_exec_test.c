/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:35 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/07 18:32:49 by nholbroo         ###   ########.fr       */
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
	int		stat_loc;
	int		exit_code;
	t_list	*current;
	t_token	*token;

	current = (t_list *)data->tok.tok_lst;
	token = (t_token *)current->content;
	while (exec->curr_child < data->pipe_nr + 1)
	{
		create_pipe(data, exec);
		pid = fork(); // Remember to protect!
		if (!pid)
			execution(data, exec, token->position);
		handle_pipe_in_parent(data, exec);
		exec->child->nbr[exec->curr_child++] = pid;
		while (token->type != PIPE && current)
		{
			current = current->next;
			if (current)
				token = (t_token *)current->content;
		}
		if (current && current->next)
			token = (t_token *)current->next->content;
	}
	close_pipe_in_parent(data, exec);
	if (waitpid(pid, &stat_loc, 0) == -1)
	{
		free_exec(exec);
		free_data(data, 1);
		exit(errno);
	}
	if (WIFEXITED(stat_loc))
	{
		exit_code = WEXITSTATUS(stat_loc);
		data->exit_status = exit_code;
	}
}

void	reset_exec(t_exec *exec)
{
	exec->count_flags = 0;
	exec->cmd_found = 0;
	exec->first = 1;
	if (exec->cmd)
	{
		free(exec->cmd);
		exec->cmd = NULL;
	}
	if (exec->flags)
	{
		ft_freearray(exec->flags);
		exec->flags = NULL;
	}
}

void	check_file_exist_parent(t_data *data, t_exec *exec)
{
	if (exec->redir_in)
	{
		if (access(exec->infile, F_OK) == -1)
			redirections_errors(data, exec, 0, 1);
	}
	if (exec->redir_out)
	{
		if (access(exec->outfile, F_OK == -1))
		{
			if (open(exec->outfile, O_CREAT) == -1)
				redirections_errors(data, exec, 1, 1);
		}
	}
}

static int	execution_only_in_parent(t_data *data, t_exec *exec)
{
	check_redirections(data, exec, 0);
	check_file_exist_parent(data, exec);
	data->exit_status = builtin(data, exec);
	free_exec(exec);
	return (0);
}

/*Initializes the exec struct. Allocates memory for an int array that will store
the pid's of the child processes.*/
int	init_exec(t_data *data)
{
	t_exec	*exec;

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
	if (data->pipe_nr == 0)
	{
		get_flags_and_command(data, exec, 0);
		if (is_parent_builtin(exec))
			return (execution_only_in_parent(data, exec));
		else
			reset_exec(exec);
	}
	create_child_processes(data, exec);
	return (free_exec(exec));
}
