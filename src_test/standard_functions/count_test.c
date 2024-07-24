/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:36:17 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 16:35:30 by nholbroo         ###   ########.fr       */
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
