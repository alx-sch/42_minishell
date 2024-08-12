/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_only_parent_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:03:20 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/12 19:04:50 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			exec->outfile_fd = open(exec->outfile, O_CREAT);
			if (exec->outfile_fd == -1)
				redirections_errors(data, exec, 1, 1);
			close(exec->outfile_fd);
			exec->outfile_fd = 0;
		}
	}
}

int	execution_only_in_parent(t_data *data, t_exec *exec)
{
	check_redirections(data, exec, 0);
	check_file_exist_parent(data, exec);
	data->exit_status = builtin(data, exec);
	free_exec(exec);
	return (0);
}
