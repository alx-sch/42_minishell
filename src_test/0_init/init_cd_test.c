/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cd_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:47:06 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 22:02:12 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN FILE:

void	init_cd_struct(t_cd **cd, char *input);

// Initializes the cd-struct (built-in).
void	init_cd_struct(t_cd **cd, char *input)
{
	*cd = malloc(sizeof(t_cd));
	if (!(*cd))
		print_error_cd(1, cd); // @Busedame: Conditinal jump + still reachables, if malloc fails
	(*cd)->component = ft_split(input, ' ');
	if (!(*cd)->component)
		print_error_cd(1, cd); // @Busedame: Conditinal jump + still reachables, if malloc fails
	(*cd)->home_user = NULL;
	(*cd)->parentdirectory = NULL;
	(*cd)->subdirectory = NULL;
}
