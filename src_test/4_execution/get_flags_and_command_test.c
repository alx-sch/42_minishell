/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags_and_command_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 15:57:18 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Allocates memory for exec->flags depending on count (cmd + flags). Moves until
the position of where the command starts (which has been updated to start
after potential redirection and filename). Then stores the command in
exec->cmd and the command + flags in exec->flags.*/
void	set_flags_and_cmd(t_data *data, t_exec *exec, int position, int count)
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
		move_current_and_update_token(&current, &token);
	exec->cmd = ft_strdup(token->lexeme);
	if (!exec->cmd)
		exec_errors(data, exec, 1);
	while (i < count && token->type != REDIR_IN && token->type != REDIR_OUT)
	{
		exec->flags[i] = ft_strdup(token->lexeme);
		if (!exec->flags[i])
			exec_errors(data, exec, 1);
		move_current_and_update_token(&current, &token);
		i++;
	}
	exec->flags[i] = NULL;
}

/*Finds the right position in the input string, depending on the position
where current child process should start reading from - up until next pipe 
or end of input. Stores the first encountered command (what is not redirection
and not a filename following a redirection, and saves the position of that
command. Keeps track of the count of command + flags. In the end calls the 
function "set_flags_and_cmd".*/
void	get_flags_and_command(t_data *data, t_exec *exec, int position)
{
	t_list	*current;
	t_token	*token;

	current = (t_list *)data->tok.tok_lst;
	token = (t_token *)current->content;
	while (token->position != position)
		move_current_and_update_token(&current, &token);
	while (current && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT 
			|| token->type == APPEND_OUT || token->type == HEREDOC)
			move_current_and_update_token(&current, &token);
		else
		{
			if (exec->first)
			{
				position = token->position;
				exec->first = 0;
			}
			exec->count_flags++;
		}
		move_current_and_update_token(&current, &token);
	}
	set_flags_and_cmd(data, exec, position, exec->count_flags);
}
