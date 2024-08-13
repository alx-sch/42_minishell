/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/08 13:51:36 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_exec *exec)
{
	if (!ft_strcmp(exec->cmd, "unset") || !ft_strcmp(exec->cmd, "echo")
		|| !ft_strcmp(exec->cmd, "exit") || !ft_strcmp(exec->cmd, "cd")
		|| !ft_strcmp(exec->cmd, "export") || !ft_strcmp(exec->cmd, "env")
		|| !ft_strcmp(exec->cmd, "pwd"))
		return (1);
	return (0);
}

int	is_parent_builtin(t_exec *exec)
{
	if (!ft_strcmp(exec->cmd, "cd") || !ft_strcmp(exec->cmd, "unset")
		|| !ft_strcmp(exec->cmd, "exit") || (!ft_strcmp(exec->cmd, "export")
			&& exec->flags[1]))
		return (1);
	return (0);
}
