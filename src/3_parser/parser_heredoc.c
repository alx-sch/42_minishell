/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/27 15:33:37 by aschenk          ###   ########.fr       */
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
Used in handle_heredoc_input().

Writes a line of text followed by a newline character to a specified fd.

 @param fd 			The file descriptor to which the line will be written.
 					This should be the file descriptor associated with the
					heredoc.
 @param input_line 	A string containing the line of text to be written.
 					The function will free this memory after writing.

 @return	`1` if both the line and the newline char were successfully written;
 			`0` if either write operation failed.
*/
static int	write_to_fd(int fd, char **input_line)
{
	int		bytes_written_1;
	int		bytes_written_2;
	char	*line;

	line = *input_line;
	bytes_written_1 = write(fd, line, ft_strlen(line));
	bytes_written_2 = write(fd, "\n", 1);
	free(line);
	*input_line = NULL;
	if (bytes_written_1 == -1 || bytes_written_2 == -1)
		return (0);
	return (1);
}

/**
Used in handle_heredoc_input().

Reads a line of input from stdin, optionally processes it to perform
variable expansion, and trims the newline character.

 @param input_line 	A pointer to a string that will be allocated and populated
 					with the line of input read from stdin.
 @param data 		The data struct containing the local list of env.
 @param expansion	A flag indicating whether variable expansion should be
 					performed (`1` for expansion, `0` otherwise).

 @return			`2` if the EOT char was encountered (Ctrl + D).
 					`1` if the line was successfully read and processed;
 					`0` if reading or processing failed.
 */
static int	read_and_process_line(char **input_line, t_data *data,
	int expansion)
{
	int	expansion_result;

	*input_line = readline(HEREDOC_P);
	if (!*input_line)
		return (2);
	if (expansion)
	{
		expansion_result = expand_variables(input_line, data, 1);
		if (!expansion_result)
		{
			free(*input_line);
			return (0);
		}
	}
	return (1);
}

/**
Used in process_heredoc().

Handles the heredoc input based on whether variable expansion is required.
Reads lines from stdin and writes them to the specified heredoc fd
until the specified delimiter is encountered. Optionally performs variable
expansion on input lines. The function also handles interruptions by CTRL+C.

 @param fd	 		The heredoc's fd.
 @param delimiter 	The delimiter that signals the end of input.
 @param data 		Pointer to data struct.
 @param expansion 	Flag indicating whether variable expansion should be
 					performed (`0` no expansion, otherwise: expansion).

 @return	`2` if the EOT char was encountered (Ctrl + D).
 			`1` if input handling succeeded and the delimiter was encountered.
 			`0` if input handling failed due to a write operation error.
 			`-1` if the heredoc input was interrupted by CTRL + C.
*/
static int	handle_heredoc_input(int fd, char *delimiter, t_data *data,
	int expansion)
{
	char	*input_line;
	int		return_val;

	return_val = read_and_process_line(&input_line, data, expansion);
	if (return_val == 0 || return_val == 2)
		return (return_val);
	while (!g_signal && ft_strcmp(input_line, delimiter) != 0)
	{
		if (!write_to_fd(fd, &input_line))
			return (0);
		return_val = read_and_process_line(&input_line, data, expansion);
		if (return_val == 0 || return_val == 2)
			return (return_val);
	}
	if (input_line)
		free(input_line);
	if (g_signal)
		return (-1);
	return (1);
}

/**
Used in process_heredocs().

Processes a single HEREDOC token by creating a file for the heredoc, handling
the input from the user, and converting the HEREDOC into REDIR_IN tokens.
Expansion of variables within the heredoc is only performed, when the
untrimmed delimiter (`next_token->lexeme`)does not contain any quotation symbols.

 @param data	 		Pointer to data struct.
 @param current_token 	The current token, which is a HEREDOC token
 @param next_token 		The next token, which is the untrimmed delimiter.
 @param trim_delimiter 	The trimmed delimiter (paired quotes removed).

 @return	`2` if EOT char was encountered (Ctrl + D).
 			`1` if the HEREDOC processing succeeded.
			`0` if the HEREDOC processing failed.
			`-1` if heredoc prompt was interrupted by CTRL + C.
*/
static int	process_heredoc(t_data *data, t_token *current_token,
	t_token *next_token, char *trim_delimiter)
{
	int		fd;
	int		return_val;

	fd = get_heredoc_fd(data);
	if (fd < 0)
		return (0);
	if (contains_quotes(next_token->lexeme))
		return_val = handle_heredoc_input(fd, trim_delimiter, data, 0);
	else
		return_val = handle_heredoc_input(fd, trim_delimiter, data, 1);
	if (return_val <= 0)
	{
		close(fd);
		return (return_val);
	}
	close(fd);
	if (!convert_tokens(data, current_token, next_token))
		return (0);
	if (return_val == 2)
		handle_eot_heredoc(trim_delimiter);
	return (1);
}

/**
Processes all HEREDOC tokens in the token list. Traverses the list,
converts HEREDOC tokens to REDIR_IN tokens, and handles HEREDOC input.
Also counts the number of PIPE tokens and sets counter accordingly.

 @return	`2` if the HEREDOC was closed by the EOT char (Ctrl + D).
 			`1` if all HEREDOCs were processed successfully or
 			none were encountered.
			`0` if any HEREDOC processing or delimiter trimming failed.
			`-1` if heredoc prompt was interrupted by CTRL+C.
			`-2` if EOT char is encountered in readline() via CTRL+D.
*/
int	process_heredocs(t_data *data)
{
	char	*t_delim;
	int		return_val;

	return_val = 42;
	data->tok.curr_node = data->tok.tok_lst;
	while (data->tok.curr_node != NULL)
	{
		data->tok.curr_tok = (t_token *)data->tok.curr_node->content;
		count_pipes(data, data->tok.curr_tok);
		if (data->tok.curr_tok->type == HEREDOC)
		{
			data->tok.next_tok = (t_token *)data->tok.curr_node->next->content;
			t_delim = trim_paired_quotes(data->tok.next_tok->lexeme);
			if (!t_delim)
				return (0);
			return_val = process_heredoc(data, data->tok.curr_tok,
					data->tok.next_tok, t_delim);
			free(t_delim);
			if (return_val == 0)
				return (0);
		}
		data->tok.curr_node = data->tok.curr_node->next;
	}
	return (return_val);
}
