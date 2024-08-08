/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:31:04 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/08 14:19:14 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees all the pid-values of the array in the child-struct.*/
void	free_children(t_child *child)
{
	if (child)
	{
		if (child->nbr)
			free(child->nbr);
		free(child);
	}
}

/*Frees all allocated memory in the exec-struct.*/
int	free_exec(t_exec *exec)
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
	return (0);
}
