/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:43:52 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/25 15:49:37 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_count_export(t_env *envp_temp)
{
	while (envp_temp)
	{
		envp_temp->printed = 0;
		envp_temp = envp_temp->next;
	}
}

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

t_env   *init_export_list(t_data *data)
{
	t_env	*current;
	t_env	*lowest_node;
	int		len;
	int		count;

	len = list_length(data->envp_temp);
	reset_count_export(data->envp_temp);
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
