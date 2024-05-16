/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_struct_inits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:28:08 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/15 13:59:51 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	(*cd)->username = NULL;
}
