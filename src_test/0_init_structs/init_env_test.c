/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:28:08 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 19:46:00 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adding a new node to the envp_temp list.
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

// Initializing a node of the envp_temp list.
static t_env	*init_node_of_env(char *envp, t_env *node)
{
	node->e_var = ft_substr(envp, 0, ft_strrchr_index(envp, '='));
	if (!node->e_var)
		mem_alloc_fail_env(&node);
	node->value = ft_substr(envp, ft_strrchr_index(envp, '=') + 1, \
	ft_strlen(envp));
	if (!node->value)
		mem_alloc_fail_env(&node);
	node->next = NULL;
	node->previous = NULL;
	node->printed = 0;
	return (node);
}

// Initializing the envp_temp list. Essentially copies the "envp"-array
// into a new linked list.
t_env	*init_env_tmp(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = 1;
	head = malloc(sizeof(t_env));
	if (!head)
		mem_alloc_fail_env(&head);
	head = init_node_of_env(envp[0], head);
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			mem_alloc_fail_env(&head);
		node = init_node_of_env(envp[i++], node);
		ft_env_tmp_add_back(&head, node);
	}
	return (head);
}
