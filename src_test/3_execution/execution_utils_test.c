/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:06:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 14:07:18 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_list(t_data *data)
{
	t_env	*current;
	int		count;

	current = data->envp_temp;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
