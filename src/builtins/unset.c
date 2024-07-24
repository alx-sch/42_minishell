/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 15:58:12 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Removes a node from the t_env list.
@param e_var "Environmental variable"
@param value "Value of the environmental variable"
@param current "The current node"*/
static void	unset_remove_variable(t_env **current, t_env **envp_temp, char *arg)
{
	while (*current)
	{
		if (ft_strncmp(arg, (*current)->e_var, ft_strlen(arg)) == 0)
		{
			if ((*current)->next)
				(*current)->next->previous = (*current)->previous;
			if ((*current)->previous)
				(*current)->previous->next = (*current)->next;
			else
				*envp_temp = (*current)->next;
			free((*current)->value);
			free((*current)->e_var);
			free(*current);
			break ;
		}
		*current = (*current)->next;
	}
}

/*Removes one or more environmental variable(s) from the env-list or 
export-list. The function is called twice in the file parsing.c, making sure 
both lists are updated. If no variables are specified or the variable doesn't
exist, nothing happens.*/
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

/*Checking if the input is "unset", ignoring whitespaces before "unset", 
and not accepting options.*/
int	is_unset(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
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
	if (input[i] && !is_whitespace(input[i]))
		return (0);
	while (input[i] != '\0')
	{
		if (!is_whitespace(input[i]))
			return (unset_err_invalid_option(input, i));
		i++;
	}
	return (1);
}
