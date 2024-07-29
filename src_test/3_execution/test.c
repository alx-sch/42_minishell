/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:35 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/29 18:46:14 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_children(t_child *child)
{
	int	i;

	i = 0;
	if (child)
	{
		if (child->nbr)
			free(child->nbr);
		free(child);
	}
}

static void	free_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->all_paths)
			ft_freearray(exec->all_paths);
		if (exec->child)
			free_children(exec->child);
		if (exec->cmd)
			free(exec->cmd);
		if (exec->current_path)
			free(exec->current_path);
		if (exec->flags)
			ft_freearray(exec->flags);
		if (exec->input)
			ft_freearray(exec->input);
		free(exec);
	}
}

static void	exec_errors(t_data *data, t_exec *exec, int error_code)
{
	if (error_code == 1)
	{
		ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
		ft_putstr_fd("minishell: exec: Cannot allocate memory\n", STDERR_FILENO);
		free_exec(exec);
		free_data(data, 1);
		exit(errno);
	}
}

t_exec	*set_exec_members_to_null(t_exec *exec)
{
	exec->all_paths = NULL;
	exec->cmd = NULL;
	exec->current_path = NULL;
	exec->flags = NULL;
	exec->input = NULL;
	exec->child = NULL;
	return (exec);
}

// static void	execution(t_data *data, t_exec *exec)
// {
	
// }

static void	create_child_processes(t_data *data, t_exec *exec)
{
	int		curr_child;
	pid_t	pid;
	int		*stat_loc;

	curr_child = 0;
	pid = 1;
	stat_loc = NULL;
	while (curr_child < data->pipe_no + 1)
	{
		if (pid)
		{
			pid = fork();
			exec->child->nbr[curr_child++] = pid;
			waitpid(pid, stat_loc, 0);
		}
		if (!pid)
			break ;
	}
	if (!pid)
	{
		//execution(data, exec);
		printf("%d\n", curr_child);
		free_exec(exec);
		free_data(data, 1);
		exit(0);
	}
	else
		return ;
}

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
