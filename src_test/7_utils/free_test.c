/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:12:15 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/14 02:20:50 by aschenk          ###   ########.fr       */
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
void	delete_heredocs(t_data *data);
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
Changes made by access() do not  affect the subsequent error handling or
reporting, as errno updated by this function are skipped.
*/
void	delete_heredocs(t_data *data)
{
	int		pipe_nr_max;
	char	*heredoc;
	int		tmp_errno;

	pipe_nr_max = data->pipe_nr;
	data->pipe_nr = 0;
	while (data->pipe_nr <= pipe_nr_max)
	{
		heredoc = get_heredoc(data);
		if (heredoc)
		{
			tmp_errno = errno;
			if (access(heredoc, F_OK) != -1)
			{
				if (unlink(heredoc) != 0)
					print_err_msg(ERR_DEL_HEREDOC);
			}
			errno = tmp_errno;
			free(heredoc);
		}
		data->pipe_nr++;
	}
}

/**
Frees all resources allocated within the minishell program.
This includes deallocating memory for tokens, and input strings.
If the function is called within an 'exit' context, also allocated memory
for absolute paths (working directory, history file), and the export as well
as environment variable list are freed.

 @param data Pointer to the t_data structure containing all allocated resources.
 @param exit Boolean flag indicating whether to free environment variables and
 			 export lists, as well as allocated paths to wd and history file.
*/
void	free_data(t_data *data, bool exit)
{
	if (!data)
		return ;
	ft_lstclear(&data->tok.tok_lst, del_token);
	if (data->input)
		free(data->input);
	data->pipe_nr = 0; // reset number of pipes to default.
	if (exit)
	{
		if (data->working_dir)
			free(data->working_dir);
		if (data->path_to_hist_file)
			free(data->path_to_hist_file);
		if (data->envp_temp)
			free_env_struct(&data->envp_temp);
		if (data->export_list)
			free_env_struct(&data->export_list);
	}
}
