/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/15 17:10:16 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_cd(int error_code, t_cd **cd)
{
	if (error_code == 1)
	{
		free_cd_struct(cd);
		errno = ENOMEM;
		printf("%s\n", strerror(errno));
		exit(1);
	}
	else if (error_code == 2)
		printf("cd: %s\n", strerror(errno));
	else if (error_code == 3)
	{
		write(2, "test\n", 5);
		free_cd_struct(cd);
	}
}
