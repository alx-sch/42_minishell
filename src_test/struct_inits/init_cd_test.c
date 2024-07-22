/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cd_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:47:06 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 19:40:09 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initializes the cd-struct.
void	init_cd_struct(t_cd **cd, char *input)
{
	*cd = malloc(sizeof(t_cd));
	if (!(*cd))
		print_error_cd(1, cd);
	(*cd)->component = ft_split(input, ' ');
	if (!(*cd)->component)
		print_error_cd(1, cd);
	(*cd)->home_user = NULL;
	(*cd)->parentdirectory = NULL;
	(*cd)->subdirectory = NULL;
}
