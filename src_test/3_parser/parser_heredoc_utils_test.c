/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/07 17:20:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains utility functions for processing heredocs, namely the
creation of heredoc files and processing  heredoc input.
*/

#include "minishell.h"

// IN FILE:

void	count_pipes(t_data *data, t_token *node);
void	trim_newline(char *str);
char	*get_heredoc(t_data *data);
int		get_heredoc_fd(t_data *data);

// Increments the pipe counter when a PIPE token is encountered.
void	count_pipes(t_data *data, t_token *node)
{
	if (node->type == PIPE)
		data->pipe_nr += 1;
}

/**
Trims the trailing newline character from a heredoc string.
This makes comparing the heredoc delimiter with the heredoc input
more straightforward.
*/
void	trim_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

/**
 @return	A heredoc filename based on the HEREDOC_PREFIX and the
 			current pipe count or `NULL` on malloc failure.
*/
char	*get_heredoc(t_data *data)
{
	char	*index;
	char	*heredoc;

	index = ft_itoa(data->pipe_nr);
	if (!index)
		return (NULL);
	heredoc = ft_strjoin(HEREDOC_PREFIX, index);
	free(index);
	return (heredoc);
}

/**
Creates and opens a heredoc file

 @return	The heredoc's file descriptor or
 			`-1` on malloc/open failure.
*/
int	get_heredoc_fd(t_data *data)
{
	char	*heredoc;
	int		fd;

	heredoc = get_heredoc(data);
	if (!heredoc)
		return (-1);
	fd = open(heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(heredoc);
	return (fd);
}

/**
Trims the quotes from around a delimiter string and returns a newly allocated
string containing the trimmed delimiter.

 @param delimiter 	The original delimiter string, which may be surrounded
 					by quotes or empty.
 @return 	A newly allocated string with the surrounding quotes removed.
 			If the original delimiter is empty, an empty string is returned.
			Returns `NULL` if memory allocation fails.
*/
char	*trim_delimiter(const char *delimiter)
{
	size_t	len;
	char	*trimmed_delim;

	len = ft_strlen(delimiter); // length of untrimmed delimiter
	trimmed_delim = NULL;
	trimmed_delim = malloc(len * sizeof(char) - 1); // len - 2 (remove beginning and end quote) + 1  (for null terminator)
	if (!trimmed_delim)
		return (NULL);
	ft_strlcpy(trimmed_delim, delimiter + 1, len - 1); // Copy the substring excluding the first and last characters
	trimmed_delim[len - 2] = '\0'; // Null-terminate
	return (trimmed_delim);
}


// Helper function to determine if a character is a quote
// bool is_quote(char c) {
//     return c == '"' || c == '\'';
// }

// char *trim_delimiter(const char *delimiter)
// {
//     if (!delimiter)
//         return NULL;

//     size_t len = strlen(delimiter);
//     size_t start = 0;
//     size_t end = len - 1;

//     // Flags to keep track of whether we're inside a quote
//     bool in_single_quote = false;
//     bool in_double_quote = false;

//     // Skip leading quotes
//     while (start < len && is_quote(delimiter[start]))
//     {
//         if (delimiter[start] == '\'') {
//             if (!in_double_quote)
//                 in_single_quote = !in_single_quote;
//         }
//         else if (delimiter[start] == '"') {
//             if (!in_single_quote)
//                 in_double_quote = !in_double_quote;
//         }
//         start++;
//     }

//     // Skip trailing quotes
//     while (end > start && is_quote(delimiter[end]))
//     {
//         if (delimiter[end] == '\'') {
//             if (!in_double_quote)
//                 in_single_quote = !in_single_quote;
//         }
//         else if (delimiter[end] == '"') {
//             if (!in_single_quote)
//                 in_double_quote = !in_double_quote;
//         }
//         end--;
//     }

//     // If end is less than start, it means there are no characters left
//     if (end < start)
//         return strdup(""); // Return an empty string

//     // Allocate memory for the new string
//     size_t new_len = end - start + 1;
//     char *result = malloc(new_len + 1);
//     if (!result)
//         return NULL; // Memory allocation failed

//     // Copy the trimmed content
//     strncpy(result, delimiter + start, new_len);
//     result[new_len] = '\0'; // Null-terminate

//     return result;
// }
