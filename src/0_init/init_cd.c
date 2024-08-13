/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cd_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:47:06 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/13 16:04:44 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN FILE:

void	init_cd_struct(t_cd **cd);

// Initializes the cd-struct (built-in).
void	init_cd_struct(t_cd **cd)
{
	*cd = malloc(sizeof(t_cd));
	if (!(*cd))
		print_error_cd(1, cd);
	(*cd)->home_user = NULL;
	(*cd)->parentdirectory = NULL;
	(*cd)->subdirectory = NULL;
}
