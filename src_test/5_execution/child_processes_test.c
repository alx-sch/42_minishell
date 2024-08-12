/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:59:35 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/12 19:19:29 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_child_processes(t_data *data, t_exec *exec)
{
	ft_putstr_fd(ERR_COLOR, 2);
	perror("");
	ft_putstr_fd(RESET, 2);
	free_exec(exec);
	free_data(data, 1);
	exit(errno);
}

static void	set_exit_code(t_data *data, int stat_loc)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(stat_loc))
	{
		exit_code = WEXITSTATUS(stat_loc);
		data->exit_status = exit_code;
	}
}

static void	finish_children(pid_t pid, int stat_loc, t_data *data, t_exec *exec)
{
	close_pipe_in_parent(data, exec);
	if (waitpid(pid, &stat_loc, 0) == -1)
		error_child_processes(data, exec);
	set_exit_code(data, stat_loc);
}

/*Creates the necessary child processes, one per command. Creates one common
pipe for all the processes, while always saving a pointer to each side of the
pipe in a different variable. */
void	create_child_processes(t_data *data, t_exec *exec)
{
	pid_t	pid;
	int		stat_loc;
	t_list	*current;
	t_token	*token;

	current = (t_list *)data->tok.tok_lst;
	token = (t_token *)current->content;
	stat_loc = 0;
	while (exec->curr_child < data->pipe_nr + 1)
	{
		create_pipe(data, exec);
		pid = fork();
		if (pid == -1)
			error_child_processes(data, exec);
		if (!pid)
			execution(data, exec, token->position);
		handle_pipe_in_parent(data, exec);
		exec->child->nbr[exec->curr_child++] = pid;
		while (token->type != PIPE && current)
			move_current_and_update_token(&current, &token);
		if (current && current->next)
			token = (t_token *)current->next->content;
	}
	finish_children(pid, stat_loc, data, exec);
}
