/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/16 12:36:46 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(char *input, char **envp)
{
	if (!ft_strcmp(input, "pwd"))
		pwd();
	else if (ft_strnstr(input, "cd", sizeof(input)) != NULL)
		cd(input, envp);
	else if (!ft_strcmp(input, "exit"))
		exit(0);
}
