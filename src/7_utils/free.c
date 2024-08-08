/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:12:15 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 14:21:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file provides functions for freeing memory and cleaning up resources
used in the minishell, including tokens, heredoc files, and data structures.
*/

#include "minishell.h"

// IN FILE:

void	del_token(void *content);
void	free_unlinked_token(t_data *data);
void	free_data(t_data *data, bool exit);

/*
Function used within the wrapper function ft_lstclear() to delete and
clean up the linked list nodes used for tokenization.
*/
void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	free(token->lexeme);
	free(token);
}

/*
Frees memory allocated for the token data structure in case of failure
during token creation in create_tok().
*/
void	free_unlinked_token(t_data *data)
{
	if (data->tok.new_node)
		free(data->tok.new_node);
	if (data->tok.tok)
	{
		if (data->tok.tok->lexeme)
			free(data->tok.tok->lexeme);
		free(data->tok.tok);
	}
}

/**
Deletes any temporary heredoc files created during shell operation.
It iterates through potential heredoc files and removes them if they exist.
*/
static void	delete_heredocs(t_data *data)
{
	int		pipe_nr_max;
	char	*heredoc;

	pipe_nr_max = data->pipe_nr;
	data->pipe_nr = 0;
	while (data->pipe_nr <= pipe_nr_max)
	{
		heredoc = get_heredoc(data);
		if (heredoc)
		{
			if (access(heredoc, F_OK) != -1)
				if (unlink(heredoc) != 0)
					print_err_msg(ERR_DEL_HEREDOC);
			free(heredoc);
		}
		data->pipe_nr++;
	}
}

/**
Frees all resources allocated within the minishell program.
This includes deallocating memory for tokens, input strings, and temporary
files used for heredocs.

Optionally, it also frees environment variables and export lists if exit is true.

 @param data Pointer to the t_data structure containing all allocated resources.
 @param exit Boolean flag indicating whether to free environment variables and
 			 export lists.
*/
void	free_data(t_data *data, bool exit)
{
	if (!data)
		return ;
	ft_lstclear(&data->tok.tok_lst, del_token);
	if (data->input)
		free(data->input);
	delete_heredocs(data);
	data->pipe_nr = 0;
	if (exit)
	{
		if (data->envp_temp)
			free_env_struct(&data->envp_temp);
		if (data->export_list)
			free_env_struct(&data->export_list);
	}
}
