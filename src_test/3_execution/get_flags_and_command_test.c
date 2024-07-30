/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags_and_command_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 20:04:18 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	helper_function(t_data *data, t_exec *exec, int position, int count)
{
	t_list	*current;
	t_token	*token;
	int		i;

	i = 0;
	exec->flags = malloc(sizeof(char *) * (count + 1));
	if (!exec->flags)
		exec_errors(data, exec, 1);
	current = (t_list *)data->tok.tok_lst;
	token = (t_token *)current->content;
	while (current && token->position != position)
	{
		current = current->next;
		if (current)
			token = (t_token *)current->content;
	}
	exec->cmd = ft_strdup(token->lexeme);
	if (!exec->cmd)
		exec_errors(data, exec, 1);
	while (i < count && token->type != REDIR_IN && token->type != REDIR_OUT)
	{
		exec->flags[i] = ft_strdup(token->lexeme);
		if (!exec->flags[i])
			exec_errors(data, exec, 1);
		current = current->next;
		if (current)
			token = (t_token *)current->content;
		i++;
	}
	exec->flags[i] = NULL;
}

void	get_flags_and_command(t_data *data, t_exec *exec, int position)
{
	t_list	*current;
	t_token	*token;
	int		count;
	bool	first;

	current = (t_list *)data->tok.tok_lst;
	token = (t_token *)current->content;
	count = 0;
	first = 1;
	while (token->position != position)
	{
		current = current->next;
		token = (t_token *)current->content;
	}
	while (current && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT)
		{
			current = current->next;
			if (current)
				token = (t_token *)current->content;
		}
		else
		{
			if (first)
			{
				position = token->position;
				first = 0;
			}
			count++;
		}
		current = current->next;
		if (current)
			token = (t_token *)current->content;
	}
	helper_function(data, exec, position, count);
}
