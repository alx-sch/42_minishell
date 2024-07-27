/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:12:15 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/26 16:19:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN FILE:

void	del_token(void *content);
void	free_unlinked_token(t_data *data);
void	free_data(t_data *data, bool exit);

/*
USED AT ALL?
Frees the memory allocated for a matrix of strings
and sets all pointers to NULL.
*/
void	free_str_arr(char ***array_ptr)
{
	int		i;
	char	**array;

	i = 0;
	array = *array_ptr;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	*array_ptr = NULL;
}

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

// Frees/closes all resources allocated for the data structure.
void	free_data(t_data *data, bool exit)
{
	if (!data)
		return ;
	ft_lstclear(&data->tok.tok_lst, del_token);
	if (data->input)
		free(data->input);
	delete_heredocs(data);
	data->pipe_nr = 0; // Reset number of pipes to default.
	if (exit)
	{
		if (data->envp_temp)
			free_env_struct(&data->envp_temp);
		if (data->export_list)
			free_env_struct(&data->export_list);
	}
}
