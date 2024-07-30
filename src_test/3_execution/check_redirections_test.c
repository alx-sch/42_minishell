/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:09:36 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 19:55:31 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*If a redirection symbol '>' meaning the output should be redirected, 
it saves the information in the bool exec->redir_out and stores the filename 
of the new output source in exec->outfile.*/
static t_list	*redirect_out(t_data *data, t_exec *exec, t_list *current, \
t_token *token)
{
	exec->redir_out = 1;
	current = current->next;
	token = (t_token *)current->content;
	if (exec->outfile)
		free(exec->outfile);
	exec->outfile = ft_strdup(token->lexeme);
	if (!exec->outfile)
		exec_errors(data, exec, 1);
	return (current);
}

/*If a redirection symbol '<' meaning the input should be redirected, 
it saves the information in the bool exec->redir_in and stores the filename 
of the new input source in exec->infile.*/
static t_list	*redirect_in(t_data *data, t_exec *exec, t_list *current, \
t_token *token)
{
	exec->redir_in = 1;
	current = current->next;
	token = (t_token *)current->content;
	if (exec->infile)
		free(exec->infile);
	exec->infile = ft_strdup(token->lexeme);
	if (!exec->infile)
		exec_errors(data, exec, 1);
	return (current);
}

/*Checks if there are any redirections '>' or '<' happening in the input.*/
void	check_redirections(t_data *data, t_exec *exec, int position)
{
	t_list	*current;
	t_token	*token;

	current = (t_list *)data->tok.tok_lst;
	token = (t_token *)current->content;
	while (current && token->position != position)
	{
		current = current->next;
		if (current)
			token = (t_token *)current->content;
	}
	while (current && token->type != PIPE)
	{
		if (token->type == REDIR_IN)
			current = redirect_in(data, exec, current, token);
		else if (token->type == REDIR_OUT)
			current = redirect_out(data, exec, current, token);
		current = current->next;
		if (current)
			token = (t_token *)current->content;
	}
}
