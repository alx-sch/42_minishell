/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:59:31 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/14 17:03:06 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cd_struct(t_cd **cd)
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
			free((*cd)->home_user);
		if ((*cd)->username)
			free((*cd)->username - 5);
		free(*cd);
	}
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