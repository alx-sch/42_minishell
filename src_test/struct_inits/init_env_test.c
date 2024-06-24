/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:28:08 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 17:46:21 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*init_env_tmp(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

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
