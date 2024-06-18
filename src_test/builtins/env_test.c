/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:38:05 by natalierh         #+#    #+#             */
/*   Updated: 2024/06/03 14:07:40 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implement errors in case of "env dsafasgasg" or "env -dsdasf" or something.
// Consider storing envp in a linked list instead of an array, easier to remove/add new variables.

int is_env(char *input)
{
    int i;

    i = 0;
    while (is_space(input[i]))
        i++;
    if (input[i++] != 'e')
        return (0);
    if (input[i++] != 'n')
        return (0);
    if (input[i++] != 'v')
        return (0);
    while (input[i] != '\0')
    {
        if (!is_space(input[i]))
            return (0);
        i++;
    }
    return (1);
}

void    env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        printf("%s\n", envp[i++]);
}
