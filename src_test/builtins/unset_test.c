/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 14:15:44 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_unset_remove_variable(t_env **current, \
t_env **envp_temp, char *arg)
{
	char	*envvar;

	envvar = NULL;
	while (*current)
	{
		envvar = ft_substr((*current)->value, 11, ft_strlen((*current)->value));
		if (ft_strncmp(arg, envvar, ft_strlen(arg)) == 0)
		{
			if ((*current)->next)
				(*current)->next->previous = (*current)->previous;
			if ((*current)->previous)
				(*current)->previous->next = (*current)->next;
			else
				*envp_temp = (*current)->next;
			free((*current)->value);
			free(*current);
			if (envvar)
				free(envvar);
			break ;
		}
		if (envvar)
			free(envvar);
		*current = (*current)->next;
	}
}

static void	env_unset_remove_variable(t_env **current, \
t_env **envp_temp, char *arg)
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

void	unset(char *input, t_env **envp_temp, bool type)
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
		if (type == 0)
			env_unset_remove_variable(&current, envp_temp, args[i]);
		else if (type == 1)
			export_unset_remove_variable(&current, envp_temp, args[i]);
		i++;
	}
	ft_freearray(args);
}

int	is_unset(char *input)
{
	int	i;

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
