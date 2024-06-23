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

static void	mem_alloc_fail_env(t_env **head)
{
    free_env_struct(head);
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: env"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

static void	ft_env_tmp_add_back(t_env **head, t_env *new)
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
    if (!head->value)
        mem_alloc_fail_env(&head);
    head->next = NULL;
    head->previous = NULL;
    while (envp[i])
    {
        node = malloc(sizeof(t_env));
        if (!node)
            mem_alloc_fail_env(&head);
        node->value = NULL;
        node->previous = NULL;
        node->next = NULL;
        node->printed = false;
        ft_env_tmp_add_back(&head, node);
        node->value = ft_strdup(envp[i++]);
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
