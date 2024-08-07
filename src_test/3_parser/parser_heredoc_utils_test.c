/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/07 19:00:35 by aschenk          ###   ########.fr       */
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
This function processes a delimiter string by removing any closed single or
double quotation chars. It ensures that only the 'paired' quotes are removed,
while preserving any quotes that are nested inside.

 @param str 	The original delimiter string, which may be surrounded
 				by quotes or empty.
 @return 	A newly allocated string with the surrounding quotes removed.
 			If the original delimiter is empty, an empty string is returned.
			Returns `NULL` if memory allocation fails.
*/
char	*trim_delimiter(const char *str)
{
	char	*trimmed_str;
	int		i;
	int		trimmed_i;
	bool	in_single_quote;
	bool	in_double_quote;

	trimmed_str = malloc(sizeof(char)*(ft_strlen(str) + 1)); // Trimmed_str cannot be larger than the original one
	if (!trimmed_str)
		return (NULL);
	i = 0;
	trimmed_i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++; // Skip the quotation char
			continue ; // Skips the remaining part of the loop's body and moves to the next iteration of the while loop.
		}
		if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++; // Skip the quote
			continue ; // Skips the remaining part of the loop's body and moves to the next iteration of the while loop.
		}
		// If we are not inside quotes, or if we are inside quotes but not of the type currently handled, copy the character
		trimmed_str[trimmed_i++] = str[i++];
	}
	trimmed_str[trimmed_i] = '\0'; // Null-terminate the trimmed string
	return (trimmed_str);
}
