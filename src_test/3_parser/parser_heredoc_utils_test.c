/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/05 19:07:37 by aschenk          ###   ########.fr       */
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
