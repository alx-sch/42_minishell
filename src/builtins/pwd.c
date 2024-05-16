/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/15 17:10:04 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		printf("pwd: %s\n", strerror(errno));
}
