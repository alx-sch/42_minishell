/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/19 16:54:34 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_err_memalloc_fail(t_env **envp_temp)
{
	free_env_struct(envp_temp); // Freeing the struct.
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

static int unset_err_invalid_option(char *input, int i)
{
    if (input[i] == '-' && is_letter(input[i + 1]))
    {
        write(2, "minishell: unset: invalid option: -- '", 39);
        write(2, &input[i + 1], 1);
        write(2, "'\n", 2);
		return (0);
    }
	return (1);
}

int	is_unset(char *input)
{
    int i;

    i = 0;
    while (is_space(input[i]))
        i++;
    if (input[i++] != 'u')
        return (0);
    if (input[i++] != 'n')
        return (0);
    if (input[i++] != 's')
        return (0);
    if (input[i++] != 'e')
        return (0);
    if (input[i++] != 't')
        return (0);
    if (input[i] && !is_space(input[i]))
        return (0);
    while (input[i] != '\0')
    {
        if (!is_space(input[i]))
            return (unset_err_invalid_option(input, i));
        i++;
    }
    return (1);
}

static void	unset_remove_variable(t_env **current, t_env **envp_temp, char *arg)
{
	while (*current)
	{
		if (ft_strncmp(arg, (*current)->value, ft_strlen(arg)) == 0)
		{
			if ((*current)->next)
				(*current)->next->previous = (*current)->previous;
			if ((*current)->previous)
				(*current)->previous->next = (*current)->next;
			else
				*envp_temp = (*current)->next;
			free((*current)->value);
			free(*current);
			break ;
		}
		*current = (*current)->next;
	}
}

void	unset(char *input, t_env **envp_temp)
{
	char	**args;
	t_env	*current;
	int		i;

	current = *envp_temp;
	i = 1;
	args = ft_split(input, ' ');
	if (!args)
		unset_err_memalloc_fail(envp_temp);
	if (!args[i])
	{
		ft_freearray(args);
		return ;
	}
	while (args[i])
	{
		current = *envp_temp;
		unset_remove_variable(&current, envp_temp, args[i]);
		i++;
	}
	ft_freearray(args);
}
