/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 14:29:27 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains utility functions for processing heredocs, namely the
creation of heredoc files and processing  heredoc input.
*/

#include "minishell.h"

// IN FILE:

void	trim_newline(char *str);
char	*get_heredoc(t_data *data);
int		get_heredoc_fd(t_data *data);

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
Toggles the state of quote flags based on the current character.
If the character is a single quote (`'`) and not within a double quote,
it toggles the `in_single_quote` flag. If the character is a double quote (`"`)
and not within a single quote, it toggles the `in_double_quote` flag.

 @param ch 					The current character being processed.
 @param in_single_quote 	Flag indicating if single quotes are active.
 @param in_double_quote 	Flag indicating if double quotes are active.

 @return 					`true` if the character is a quote that is paired;
 							`false` otherwise.
*/
static bool	handle_quote(char ch, bool *in_single_quote, bool *in_double_quote)
{
	if (ch == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
		return (true);
	}
	if (ch == '"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
		return (true);
	}
	return (false);
}

/**
Processes a heredoc delimiter string by removing paired single and double
quotation characters. Nested quote characters are preserved.

 @param str 	The original delimiter string, which may include paired quotes.

 @return 	A newly allocated string with all paired quotes removed.
			Returns `NULL` if memory allocation fails.
*/
char	*trim_delimiter(const char *str)
{
	char	*trimmed_str;
	int		i;
	int		trimmed_i;
	bool	in_single_quote;
	bool	in_double_quote;

	trimmed_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	trimmed_i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (str[i])
	{
		if (handle_quote(str[i], &in_single_quote, &in_double_quote))
			i++;
		else
			trimmed_str[trimmed_i++] = str[i++];
	}
	trimmed_str[trimmed_i] = '\0';
	return (trimmed_str);
}
