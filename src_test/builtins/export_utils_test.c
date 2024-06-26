/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:50:31 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/26 15:56:01 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*check_if_envar_exists(t_env *env_list, char *arg)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->e_var, arg, ft_strchr_index(arg, '=')) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}


void	add_env_var_no_value(t_data *data, char *arg)
{
	t_env	*node;

	if (check_if_envar_exists(data->export_list, arg))
		return ;
	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->previous = NULL;
	node->e_var = ft_strdup(arg);
	node->value = NULL;
	node->printed = 0;
	ft_env_tmp_add_back(&data->export_list, node);
}

void	add_env_var_export_with_value(t_data *data, char *arg)
{
	t_env	*node;

	if (!check_if_envar_exists(data->export_list, arg))
	{
		node = malloc(sizeof(t_env));
		node->next = NULL;
		node->previous = NULL;
		node->e_var = ft_substr(arg, 0, ft_strchr_index(arg, '='));
		node->value = ft_substr(arg, ft_strchr_index(arg, '=') + 1, \
		ft_strlen(arg));
		node->printed = 0;
		ft_env_tmp_add_back(&data->export_list, node);
	}
	else
	{
		node = check_if_envar_exists(data->export_list, arg);
		free(node->value);
		node->value = ft_substr(arg, ft_strchr_index(arg, '=') \
		+ 1, ft_strlen(arg));
	}
}

void	add_env_var_envp_with_value(t_data *data, char *arg)
{
	t_env	*node;

	if (!check_if_envar_exists(data->envp_temp, arg))
	{
		node = malloc(sizeof(t_env));
		node->next = NULL;
		node->previous = NULL;
		node->e_var = ft_substr(arg, 0, ft_strchr_index(arg, '='));
		node->value = ft_substr(arg, ft_strchr_index(arg, '=') + 1, \
		ft_strlen(arg));
		node->printed = 0;
		ft_env_tmp_add_back(&data->envp_temp, node);
	}
	else
	{
		node = check_if_envar_exists(data->envp_temp, arg);
		free(node->value);
		node->value = ft_substr(arg, ft_strchr_index(arg, '=') \
		+ 1, ft_strlen(arg));
	}
}
