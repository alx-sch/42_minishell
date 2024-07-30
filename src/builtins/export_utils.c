/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:50:31 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/29 19:08:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the environmental variable already exists in the list.
// @param env_list Can be either export_list or envp_temp.
// @param arg The current argument to the "export"-command.
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

/*Adds the new environmental variable into export_list, maintaining the
alphabetical order. Also handles the case where the new node is of the
lowest alphabetical value.
@param head Beginning of the export_list.
@param node The new node (environmental variable) to be added.*/
static void	add_to_export_list_alphabetical(t_env **head, t_env *node)
{
	t_env	*current;

	if (!head || !node)
		return ;
	if (!*head || ft_strcmp((*head)->e_var, node->e_var) > 0)
	{
		node->next = *head;
		if (*head)
			(*head)->previous = node;
		*head = node;
	}
	else
	{
		current = *head;
		while (current->next && ft_strcmp(current->next->e_var, node->e_var) \
		< 0)
			current = current->next;
		node->next = current->next;
		if (current->next)
			current->next->previous = node;
		current->next = node;
		node->previous = current;
	}
}

/*Adds an environmental variable to the export-list with no value.
-If the environmental variable already exists, nothing happens.
-Otherwise a new environmental variable is created and added to the end of the
list.
@param arg The argument to the "export"-command (the name of the new
variable).*/
void	add_env_var_no_value(t_data *data, char *arg)
{
	t_env	*node;

	if (check_if_envar_exists(data->export_list, arg))
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		export_mem_alloc_failure(data);
	node->next = NULL;
	node->previous = NULL;
	node->e_var = ft_strdup(arg);
	if (!node->e_var)
		export_mem_alloc_failure(data);
	node->value = NULL;
	node->printed = 0;
	add_to_export_list_alphabetical(&data->export_list, node);
}

/*Adds or modifies an environmental variable to the export-list with a defined
value.
-If the environmental variable already exists, give it a new value.
-Otherwise create a new environmental variable, assign it a value, and
add it to the end of the list.
@param arg The argument to the "export"-command, either a new variable or
a variable + value (separated by a '='). A new variable would look like this:
"export GROUP", and assigning a value to an already existing variable: "export
NAME=JOE".*/
void	add_env_var_export_with_value(t_data *data, char *arg)
{
	t_env	*node;

	if (!check_if_envar_exists(data->export_list, arg))
	{
		node = malloc(sizeof(t_env));
		if (!node)
			export_mem_alloc_failure(data);
		node->next = NULL;
		node->previous = NULL;
		node->e_var = ft_substr(arg, 0, ft_strchr_index(arg, '='));
		node->value = ft_substr(arg, ft_strchr_index(arg, '=') + 1, \
		ft_strlen(arg));
		node->printed = 0;
		add_to_export_list_alphabetical(&data->export_list, node);
	}
	else
	{
		node = check_if_envar_exists(data->export_list, arg);
		free(node->value);
		node->value = ft_substr(arg, ft_strchr_index(arg, '=') \
		+ 1, ft_strlen(arg));
	}
	if (!node->e_var || !node->value)
		export_mem_alloc_failure(data);
}

/*Adds or modifies an environmental variable to the env-list with a defined
value.
-If the environmental variable already exists, give it a new value.
-Otherwise create a new environmental variable, assign it a value, and
add it to the end of the list.
@param arg The argument to the "export"-command, either a new variable or
a variable + value (separated by a '='). A new variable would look like this:
"export GROUP", and assigning a value to an already existing variable: "export
NAME=JOE".*/
void	add_env_var_envp_with_value(t_data *data, char *arg)
{
	t_env	*node;

	if (!check_if_envar_exists(data->envp_temp, arg))
	{
		node = malloc(sizeof(t_env));
		if (!node)
			export_mem_alloc_failure(data);
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
	if (!node->e_var || !node->value)
		export_mem_alloc_failure(data);
}
