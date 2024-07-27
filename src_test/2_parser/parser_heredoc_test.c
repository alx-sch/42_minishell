/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/27 09:11:23 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions for processing HEREDOC tokens.
It utilizes functions found in parser_heredoc_utils.c.
*/

#include "minishell.h"

// FUNCTION IN FILE

int	process_heredocs(t_data *data);

/*
Used in process_single_heredoc().

Converts HEREDOC tokens ('<< EOF') into REDIR_IN tokens ('< heredoc-file'),
where the 'EOF' lexeme is replaced by the actual filename created for heredoc.
This simplifies further processing by ensuring that HEREDOC tokens are processed
in the same way as REDIR_IN tokens.

Returns:
- 1 if HEREDOC token conversion succeeded.
- 0 if HEREDOC token conversion failed.
*/
static int	convert_tokens(t_data *data, t_token *current_token,
	t_token *next_token)
{
	char	*heredoc;

	heredoc = get_heredoc(data);
	if (!heredoc)
		return (0);
	current_token->type = REDIR_IN;
	free(next_token->lexeme);
	next_token->lexeme = ft_strdup(heredoc);
	free(heredoc);
	if (!next_token->lexeme)
		return (0);
	return (1);
}

/*
Handles input for a HEREDOC token by reading lines from stdin until the delimiter
is encountered. Writes each line to the specified file descriptor.

Returns:
- 1 if input handling succeeded.
- 0 if input handling failed (write operation failed).
*/
static int	handle_heredoc_input(int fd, const char *delimiter)
{
	char	*input_line;
	int		bytes_written_1;
	int		bytes_written_2;

	ft_printf(HEREDOC_P);
	input_line = get_next_line(STDIN_FILENO);
	trim_newline(input_line);
	while (input_line != NULL && ft_strcmp(input_line, delimiter) != 0)
	{
		bytes_written_1 = write(fd, input_line, ft_strlen(input_line));
		bytes_written_2 = write(fd, "\n", 1);
		free(input_line);
		if (bytes_written_1 == -1 || bytes_written_2 == -1) // check if writing into file was successful
			return (0);
		ft_printf(HEREDOC_P);
		input_line = get_next_line(STDIN_FILENO);
		trim_newline(input_line);
	}
	if (input_line)
		free(input_line);
	return (1);
}

/*
Processes a single HEREDOC token by creating a file for the heredoc, handling
the input from the user, and converting the HEREDOC into REDIR_IN tokens.

Returns:
- 1 if the HEREDOC processing succeeded.
- 0 if the HEREDOC processing failed.
*/
static int	process_single_heredoc(t_data *data, t_token *current_token,
	t_token *next_token)
{
	int	fd;

	fd = get_heredoc_fd(data);
	if (fd < 0)
		return (0);
	if (!handle_heredoc_input(fd, next_token->lexeme))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!convert_tokens(data, current_token, next_token))
		return (0);
	return (1);
}

/*
Processes all HEREDOC tokens in the token list. Traverses the list,
converts HEREDOC tokens to REDIR_IN tokens, and handles HEREDOC input.

Returns:
- 1 if all HEREDOCs were processed successfully.
- 0 if any HEREDOC processing failed.
*/
int	process_heredocs(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	t_token	*next_token;

	current_node = data->tok.tok_lst;
	while (current_node != NULL) // traverse the token linked list
	{
		current_token = (t_token *)current_node->content;
		count_pipes(data, current_token); // increase pipe counter if token is 'PIPE'
		if (current_token->type == HEREDOC)
		{
		 	next_token = (t_token *)current_node->next->content; // Delimiter is the token after the HEREDOC token.
			if (!process_single_heredoc(data, current_token, next_token))
				return (0);
		}
		current_node = current_node->next;
	}
	return (1);
}
