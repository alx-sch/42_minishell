/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:32:25 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 14:07:34 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	conversion_errors(t_data *data, t_exec *exec, int i)
{
	exec->envp_temp_arr[i] = NULL;
	exec_errors(data, exec, 1);
}

void	exec_errors(t_data *data, t_exec *exec, int error_code)
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
