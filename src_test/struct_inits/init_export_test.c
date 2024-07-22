/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:43:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 19:57:42 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Part of the sorting algorithm to sort the environmental variables
// alphabetically, to be stored in export_list. 
// Sets all the envp_temp->printed to 0.
// NB! WHEN YOU ADD A NEW NODE USING EXPORT, IT SHOULD BE PLACED
// ALPHABETICALLY TOO, WHICH IS NOT THE CASE NOW. 
static void	reset_printed_export(t_env *envp_temp)
{
	while (envp_temp)
	{
		envp_temp->printed = 0;
		envp_temp = envp_temp->next;
	}
}

// Checks the length of the envp_temp list (how many nodes).
static int	list_length(t_env *envp_temp)
{
	int	len;

	len = 0;
	while (envp_temp)
	{
		envp_temp = envp_temp->next;
		len++;
	}
	return (len);
}

// Adds the current lowest alphabetical value environmental variable 
// from envp_temp to export_list.
// If export_list doesn't exist, meaning it is the lowest_node is the first
// node to be added, the functin initializes export_list.
// @param lowest_node The current node that should be added to export_list.
static t_env	*build_export_list(t_data *data, t_env *lowest_node)
{
	t_env	*node;

	if (!data->export_list)
	{
		data->export_list = malloc(sizeof(t_env));
		data->export_list->next = NULL;
		data->export_list->previous = NULL;
		data->export_list->printed = 0;
		data->export_list->e_var = ft_strdup(lowest_node->e_var);
		data->export_list->value = ft_strdup(lowest_node->value);
		return (data->export_list);
	}
	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->previous = NULL;
	node->printed = 0;
	node->e_var = ft_strdup(lowest_node->e_var);
	node->value = ft_strdup(lowest_node->value);
	ft_env_tmp_add_back(&data->export_list, node);
	return (data->export_list);
}

// Initializes the export_list.
// A sorting algorithm to sort the environmental variables alphabetically.
// Iterates through the envp_temp-list, taking the element
// with the lowest alphabetical value that has NOT been stored yet, 
// and adds it to the export_list. Goes through the envp_temp-list until all
// elements have been added to export_list.
// NB! FUNCTION TOO LONG.
t_env	*init_export_list(t_data *data)
{
	t_env	*current;
	t_env	*lowest_node;
	int		len;
	int		count;

	len = list_length(data->envp_temp);
	reset_printed_export(data->envp_temp);
	count = 0;
	while (count < len)
	{
		current = data->envp_temp;
		lowest_node = NULL;
		while (current)
		{
			if (!current->printed && (!lowest_node
					|| ft_strcmp(current->e_var, lowest_node->e_var) < 0))
				lowest_node = current;
			current = current->next;
		}
		if (lowest_node)
		{
			data->export_list = build_export_list(data, lowest_node);
			lowest_node->printed = 1;
		}
		count++;
	}
	return (data->export_list);
}
