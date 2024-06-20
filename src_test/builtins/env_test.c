/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:38:05 by natalierh         #+#    #+#             */
/*   Updated: 2024/06/20 14:13:49 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The env builtin - accepts several spaces etc, but not "envv" etc.
// Prints an error in the case of "env dsafgasg" or "env -dsdasf" or something.

static int env_error_messages(char *input, int i)
{
    if (input[i] == '-' && (input[i + 1]))
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

void    env(t_env *envp_temp)
{
    while (envp_temp)
    {
        printf("%s\n", envp_temp->value);
        envp_temp = envp_temp->next;
    }
}
