/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:38:05 by natalierh         #+#    #+#             */
/*   Updated: 2024/06/19 13:27:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implement errors in case of "env dsafasgasg" or "env -dsdasf" or something.
// Consider storing envp in a linked list instead of an array, easier to remove/add new variables.

static int  is_letter(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}
static int env_error_messages(char *input, int i)
{
    if (input[i] == '-' && is_letter(input[i + 1]))
    {
        write(2, "env: invalid option: -- '", 25);
        write(2, &input[i + 1], 1);
        write(2, "'\n", 2);
    }
    else if (is_letter(input[i]))
    {
        errno = ENOENT;
        write(2, "env: ", 5);
        write(2, "'", 1);
        while (input[i] && !is_space(input[i]))
            write(2, &input[i++], 1);
        write(2, "': ", 3);
        perror("");
    }
    return (0);
}

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
    if (input[i] && !is_space(input[i]))
        return (0);
    while (input[i] != '\0')
    {
        if (!is_space(input[i]))
            return (env_error_messages(input, i));
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
