/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:12:15 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/24 19:50:43 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN FILE:

void	del_token(void *content);
void	free_unlinked_token(t_data *data);
void	free_data(t_data *data);

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

// void	free_unlinked_token(t_data *data)
// {
// 	if (data->tok.new_node)
// 		free(data->tok.new_node);
// 	if (data->tok.tok)
// 	{
// 		if (data->tok.tok->lexeme)
// 			free(data->tok.tok->lexeme);
// 		free(data->tok.tok);
// 	}
// }

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

// Frees/closes all resources allocated for the data structure.
void	free_data(t_data *data)
{
	if (!data)
		return ;
	ft_lstclear(&data->tok.tok_lst, del_token);
	//free_unlinked_token(data);
	if (data->input)
		free(data->input);
	data->pipe_no = 0; // Reset number of pipes to default.
	// prob need to free other members of the t_data struct
}
