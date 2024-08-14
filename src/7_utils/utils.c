/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/14 02:27:41 by aschenk          ###   ########.fr       */
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
void	cleanup(t_data *data, bool exit);

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

 @param data 		Pointer to a t_data structure containing the working
 					directory.
 @param path 		Pointer to a char* where the constructed file path will be
 					stored.
					The function updates this pointer to point to the newly
					allocated path.
 @param file 		The name of the file to be appended to the working directory.
 @param err_msg 	A custom error message to be printed if memory allocation
 					fails.
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

/**
Displays a command prompt to the user and reads their input.

This function uses the `readline` library to show a prompt (specified by
the `PROMPT` macro) and captures the user's input. If the user signals an
intention to exit (e.g., by pressing Ctrl+D), the function calls
`process_exit_signal` to handle the termination gracefully.

 @param data 	A pointer to the data structure. The user's input will be
 				stored in the `input` field of this structure.
*/
void	minishell_prompt(t_data *data)
{
	data->input = readline(PROMPT);
	if (!data->input)
		process_exit_signal(data, NULL);
}

/**
Cleans up resources and resets state for the next minishell prompt iteration.

 This function performs the following tasks:
 -	Deletes any temporary heredoc files created during the current loop
 	iteration to avoid leftover files and potential conflicts.
 -	Frees and resets the memory associated with the `t_data` structure to
 	prepare for new input and ensure a clean state for the next iteration.

 @param data 	A pointer to the `t_data` structure containing resources to
 				be cleaned up.
 @param exit	Boolean flag indicating whether to free environment variables and
 				export lists, as well as allocated paths to wd and history file.
*/
void	cleanup(t_data *data, bool exit)
{
	delete_heredocs(data);
	free_data(data, exit);
}
