/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:12:15 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/21 17:00:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	free(token->lexeme);
	free(token);
}

// Frees/closes all resources allocated for the data structure.
void	free_data(t_data *data)
{
	if (!data)
		return ;
	ft_lstclear(&data->tok.tok_lst, del_token);
	if (data->input)
		free(data->input);
	// might need to free other members of the t_data struct
}
