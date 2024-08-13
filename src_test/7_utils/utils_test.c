/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 11:47:06 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains utility functions used throughout the minishell project,
such as character classification.
*/

#include "minishell.h"

// IN FILE:

int		is_whitespace(int c);
int		contains_quotes(const char *str);


/**
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.

 @param c The character to check.

 @return	`1` if the character is one of the whitespace characters.
 			`0` otherwise.
*/
int	is_whitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/**
Checks if a string contains either single or double quotes.

 @param str 	The string to be checked.

 @return		`1` if the string contains at least one single or double quote.
				`0` otherwise.
*/
int	contains_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

void	set_path_to_file(t_data *data, char *file)
{
	char	init_wd[4096];

	getcwd(init_wd, sizeof(init_wd));
	data->path_to_hist_file = ft_strjoin(init_wd, file);
	if (!data->path_to_hist_file)
	{
		free_data(data, 1);
		perror("");
		exit(1);
	}
}

// // Function to print the list of tokens
// // FOR TESTING ONLY; use `print_token_list(data.tok.tok_lst)` in main().
// void	print_token_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		t_token *token = lst->content;
// 		printf("Position[%d]: '%s' (token type: %d)\n", token->position, token->lexeme, token->type);
// 		lst = lst->next;
// 	}
// }
