/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_struct_inits_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:28:08 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/19 12:39:44 by nholbroo         ###   ########.fr       */
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
    t_env   *node;
    char    *copy_lowest_node;

    copy_lowest_node = ft_strdup(lowest_node->value);
    if (!data->export_list)
	{
		data->export_list = malloc(sizeof(t_env));
        data->export_list->next = NULL;
        data->export_list->previous = NULL;
        data->export_list->printed = 0;
		data->export_list->value = ft_strjoin("declare -x ", copy_lowest_node);
        free(copy_lowest_node);
		return (data->export_list);
	}
    node = malloc(sizeof(t_env));
    node->next = NULL;
    node->previous = NULL;
    node->printed = 0;
	node->value = ft_strjoin("declare -x ", copy_lowest_node);
    ft_env_tmp_add_back(&data->export_list, node);
    free(copy_lowest_node);
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
            if (!current->printed
				&& (!lowest_node || ft_strcmp(current->value, lowest_node->value) < 0))
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

static void	mem_alloc_fail_env(t_env **head)
{
    free_env_struct(head);
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

void	ft_env_tmp_add_back(t_env **head, t_env *new)
{
	t_env	*current;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
        new->previous = current;
	}
}

t_env   *init_env_tmp(char **envp)
{
    t_env   *head;
    t_env   *node;
    int     i;

    i = 0;
    head = malloc(sizeof(t_env));
    if (!head)
        mem_alloc_fail_env(&head);
    head->value = ft_strdup(envp[i++]);
    head->next = NULL;
    head->previous = NULL;
    head->printed = 0;
    if (!head->value)
        mem_alloc_fail_env(&head);
    while (envp[i])
    {
        node = malloc(sizeof(t_env));
        if (!node)
            mem_alloc_fail_env(&head);
        node->next = NULL;
        node->previous = NULL;
        node->printed = NULL;
        node->value = ft_strdup(envp[i++]);
        ft_env_tmp_add_back(&head, node);
        if (!node->value)
            mem_alloc_fail_env(&head);
    }
    return (head);
}

void	init_cd_struct(t_cd **cd, char *input)
{
	*cd = malloc(sizeof(t_cd));
	if (!(*cd))
		print_error_cd(1, cd);
	(*cd)->component = ft_split(input, ' ');
	if (!(*cd)->component)
		print_error_cd(1, cd);
	(*cd)->home_user = NULL;
	(*cd)->parentdirectory = NULL;
	(*cd)->subdirectory = NULL;
}
