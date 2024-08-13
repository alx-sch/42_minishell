/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 17:18:53 by nholbroo         ###   ########.fr       */
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
void	set_path_to_file(t_data *data, char **str, char *file, char *err_msg);
void	minishell_prompt(t_data *data);

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

/**
Creates a full file path by combining the working directory stored in the `data`
structure with the specified `file` name. It dynamically allocates memory for the
resulting path and assigns it to the `path` pointer. If memory allocation fails,
or if any error occurs, it will print an error message and terminate the program.

 @param data 		Pointer to a t_data structure containing the working directory.
 @param path 		Pointer to a char* where the constructed file path will be stored.
					The function updates this pointer to point to the newly
					allocated path.
 @param file 		The name of the file to be appended to the working directory.
 @param err_msg 	A custom error message to be printed if memory allocation fails.
*/
void	set_path_to_file(t_data *data, char **path, char *file, char *err_msg)
{
	*path = ft_strjoin(data->working_dir, file);
	if (!*path)
	{
		free_data(data, 1);
		print_err_msg(err_msg);
		exit(EXIT_FAILURE);
	}
}

void	minishell_prompt(t_data *data)
{
	data->input = readline(PROMPT);
	if (!data->input)
		process_exit_signal(data, NULL);
}

// // Function to print the list of tokens
// // FOR TESTING ONLY; use `print_token_list(data.tok.tok_lst)` in main().
void	print_token_list(t_list *lst)
{
	while (lst)
	{
		t_token *token = lst->content;
		printf("Position[%d]: '%s' (token type: %d)\n", token->position, token->lexeme, token->type);
		lst = lst->next;
	}
}
