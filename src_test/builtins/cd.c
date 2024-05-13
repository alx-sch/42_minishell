/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/13 15:01:36 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(char *input)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
		print_error(2);
	if (!ft_strcmp(input, "cd"))
		chdir ("/home");
	else if (!ft_strcmp(input, "cd .."))
	{
		ft_strrchr()
	}
}
