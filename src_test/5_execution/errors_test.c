/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:32:25 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 16:36:46 by nholbroo         ###   ########.fr       */
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

/*Prints an error message an exits the process if the command is not found*/
void	error_incorrect_path(t_data *data, t_exec *exec)
{
	if (exec->cmd_found)
	{
		ft_putstr_fd(ERR_PREFIX, 2);
		ft_putstr_fd("Command '", 2);
		ft_putstr_fd(exec->cmd, 2);
		ft_putstr_fd("' not found\n", 2);
		free_exec(exec);
		free_data(data, 1);
		exit(errno);
	}
	free_exec(exec);
	free_data(data, 1);
	exit(0);
}

/*Makes sure to NULL-terminate the envp_temp_arr in case of memory allocation
failure somewhere along the way- so the whole array can safely be freed.*/
void	conversion_errors(t_data *data, t_exec *exec, int i)
{
	exec->envp_temp_arr[i] = NULL;
	exec_errors(data, exec, 1);
}

/*Error handling during execution, prints an error message, cleans up allocated 
memory and exits the child process.*/
void	exec_errors(t_data *data, t_exec *exec, int error_code)
{
	if (error_code == 1)
	{
		ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
		ft_putstr_fd("minishell: exec: Cannot allocate memory\n", STDERR_FILENO);
	}
	if (error_code == 2)
	{
		ft_putstr_fd(ERR_PREFIX, 2);
		ft_putstr_fd(exec->cmd, 2);
		ft_putstr_fd(": ", 2);
		errno = ENOENT;
		perror("");
	}
	if (error_code == 3)
	{
		ft_putstr_fd(ERR_PREFIX, 2);
		ft_putstr_fd("Piping failed", 2);
		perror("");
	}
	free_exec(exec);
	free_data(data, 1);
	exit(errno);
}
