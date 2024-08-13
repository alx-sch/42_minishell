/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_array_length.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:36:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/13 16:36:23 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Counts the length of an array of strings, meaning how many strings. */
int	count_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
