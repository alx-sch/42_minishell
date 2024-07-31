/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:31:04 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 22:19:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees all the pid-values of the array in the child-struct.*/
void	free_children(t_child *child)
{
	// int	i;

	// i = 0;
	if (child)
	{
		if (child->nbr)
			free(child->nbr);
		free(child);
	}
}

/*Frees all allocated memory in the exec-struct.*/
void	free_exec(t_exec *exec)
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
		if (exec->envp_temp_arr)
			ft_freearray(exec->envp_temp_arr);
		if (exec->infile)
			free(exec->infile);
		if (exec->outfile)
			free(exec->outfile);
		free(exec);
	}
}
