/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:59:31 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 12:39:33 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_struct(t_env **head)
{
	t_env	*current;
	t_env	*next_node;

	current = *head;
	if (current)
	{
		while (current)
		{
			next_node = current->next;
			free(current->value);
			free(current);
			current = NULL;
			current = next_node;
		}
	}
}

int	free_cd_struct(t_cd **cd)
{
	if (*cd)
	{
		if ((*cd)->component)
			ft_freearray((*cd)->component);
		if ((*cd)->subdirectory)
			free((*cd)->subdirectory);
		if ((*cd)->parentdirectory)
			free((*cd)->parentdirectory);
		if ((*cd)->home_user)
			free((*cd)->home_user - 5);
		free(*cd);
	}
	return (0);
}

int	ft_freearray(char **arr)
{
	int	crstr;
	int	max;

	crstr = 0;
	max = 0;
	while (arr[crstr])
	{
		crstr++;
		max++;
	}
	crstr = 0;
	while (crstr < max)
	{
		free(arr[crstr]);
		arr[crstr] = NULL;
		crstr++;
	}
	free(arr);
	arr = NULL;
	return (0);
}
