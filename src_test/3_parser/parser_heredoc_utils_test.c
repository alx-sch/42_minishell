/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 19:26:18 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains utility functions for processing heredocs, e.g. the
creation of heredoc files and processing heredoc input.
*/

#include "minishell.h"

// IN FILE:

char	*get_heredoc(t_data *data);
int		get_heredoc_fd(t_data *data);
void	trim_newline(char *str);
void	count_pipes(t_data *data, t_token *node);
int		convert_tokens(t_data *data, t_token *curr_token, t_token *next_token);

/**
Creates a heredoc filename.

 @return	A heredoc filename based on the current pipe count or
 			`NULL` on malloc failure.
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

// Increments the pipe counter when the passed token is of type PIPE.
void	count_pipes(t_data *data, t_token *node)
{
	if (node->type == PIPE)
		data->pipe_nr += 1;
}

/**
Converts HEREDOC tokens (`<< EOF`) into REDIR_IN tokens (`< heredoc-file`),
where the delimiter is replaced by the actual filename created for the heredoc.
This simplifies further processing by ensuring that HEREDOC tokens are processed
in the same way as REDIR_IN tokens.

 @return	`1` if HEREDOC token conversion succeeded.
			`0` if HEREDOC token conversion failed.
*/
int	convert_tokens(t_data *data, t_token *curr_token, t_token *next_token)
{
	char	*heredoc;

	heredoc = get_heredoc(data);
	if (!heredoc)
		return (0);
	curr_token->type = REDIR_IN;
	free(next_token->lexeme);
	next_token->lexeme = ft_strdup(heredoc);
	free(heredoc);
	if (!next_token->lexeme)
		return (0);
	return (1);
}
