/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/07 18:46:58 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for processing HEREDOC tokens.
It utilizes functions found in parser_heredoc_utils.c.
*/

#include "minishell.h"

// IN FILE:

int	process_heredocs(t_data *data);

/**
Used in process_single_heredoc().

Converts HEREDOC tokens (`<< EOF`) into REDIR_IN tokens (`< heredoc-file`),
where the delimiter is replaced by the actual filename created for the heredoc.
This simplifies further processing by ensuring that HEREDOC tokens are processed
in the same way as REDIR_IN tokens.

 @return	`1` if HEREDOC token conversion succeeded.
			`0` if HEREDOC token conversion failed.
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

/**
Handles the heredoc prompt (if delimiter not in quotes).

Reads lines from stdin and writes them to the specified file descriptor
(heredoc) until the specified delimiter is encountered. Each line isbprocessed
by expanding any variables before being written to the file descriptor.
The function also handles interruptions by CTRL+C.

 @param fd 			The file descriptor to which the input lines will be written.
 @param delimiter 	The delimiter that signals the end of input.
 @param data 		Pointer to data used for variable expansion.

 @return	`1` if input handling succeeded and the delimiter was encountered.
			`0` if input handling failed due to a write operation error.
			`-1` if the heredoc input was interrupted by CTRL+C
			(indicated by `g_signal`).
*/
static int	handle_heredoc_input(int fd, const char *delimiter, t_data *data)
{
	char	*input_line;
	int		bytes_written_1;
	int		bytes_written_2;

	ft_printf(HEREDOC_P);
	input_line = get_next_line(STDIN_FILENO);
	trim_newline(input_line);
	while (!g_signal && expand_variables(&input_line, data) == 1
		&& ft_strcmp(input_line, delimiter) != 0)
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
	if (g_signal)
		return (-1);
	return (1);
}

/**
Handles the heredoc prompt (if delimiter is in quotes).

Reads lines from stdin and writes them to the specified file descriptor
until the specified delimiter is encountered. No variable expansion is performed
on the input lines. The function also handles interruptions by CTRL+C.

 @param fd 			The file descriptor to which the input lines will be written.
 @param delimiter 	The delimiter that signals the end of input.
 @param data 		Pointer to data used for variable expansion.

 @return	`1` if input handling succeeded and the delimiter was encountered.
			`0` if input handling failed due to a write operation error.
			`-1` if the heredoc input was interrupted by CTRL+C
			(indicated by `g_signal`).
*/
static int	handle_heredoc_input_no_expansion(int fd, const char *trimmed_delim)
{
	char	*input_line;
	int		bytes_written_1;
	int		bytes_written_2;

	ft_printf(HEREDOC_P);
	input_line = get_next_line(STDIN_FILENO);
	trim_newline(input_line);
	while (!g_signal && ft_strcmp(input_line, trimmed_delim) != 0)
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
	if (g_signal)
		return (-1);
	return (1);
}

/**
Processes a single HEREDOC token by creating a file for the heredoc, handling
the input from the user, and converting the HEREDOC into REDIR_IN tokens.

 @return	`1` if the HEREDOC processing succeeded.
			`0` if the HEREDOC processing failed.
			`-1` if heredoc prompt was interrupted by CTRL+C.
*/
static int	process_single_heredoc(t_data *data, t_token *current_token,
	t_token *next_token)
{
	int		fd;
	int		return_val;
	char	*trimmed_delim;

	fd = get_heredoc_fd(data);
	if (fd < 0)
		return (0);
	if (next_token->lexeme[0] == '\'' || next_token->lexeme[0] == '\"') // check if delimiter is in quotes
	{
		trimmed_delim = trim_delimiter(next_token->lexeme); // trim leading and trailing quote from delimiter
		printf("trimmed delim: %s\n", trimmed_delim);
		return_val = handle_heredoc_input_no_expansion(fd, trimmed_delim);
		free(trimmed_delim);
	}
	else
		return_val = handle_heredoc_input(fd, next_token->lexeme, data);
	if (return_val <= 0)
	{
		close(fd);
		return (return_val);
	}
	close(fd);
	if (!convert_tokens(data, current_token, next_token))
		return (0);
	return (1);
}

/**
Processes all HEREDOC tokens in the token list. Traverses the list,
converts HEREDOC tokens to REDIR_IN tokens, and handles HEREDOC input.

 @return	`1` if all HEREDOCs were processed successfully or
 			none were encountered.
			`0` if any HEREDOC processing failed.
			`-1` if heredoc prompt was interrupted by CTRL+C.
*/
int	process_heredocs(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	t_token	*next_token;
	int		return_val;

	current_node = data->tok.tok_lst;
	while (current_node != NULL) // traverse the token linked list
	{
		current_token = (t_token *)current_node->content;
		count_pipes(data, current_token); // increase pipe counter if token is 'PIPE'
		if (current_token->type == HEREDOC)
		{
		 	next_token = (t_token *)current_node->next->content; // Delimiter is the token after the HEREDOC token.
			return_val = process_single_heredoc(data, current_token,
					next_token);
			if (return_val <= 0)
				return (return_val);
		}
		current_node = current_node->next;
	}
	return (1);
}
