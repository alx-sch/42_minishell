/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:41:46 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/01 19:49:26 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		printf("pwd: %s\n", strerror(errno));
}
