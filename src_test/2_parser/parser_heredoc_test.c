/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/25 20:11:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// FUNCTION IN FILE

static void	count_pipes(t_data *data, t_token *node)
{
	//printf("token type: %d\n", node->type);
	if (node->type == PIPE)
		data->pipe_nr += 1;
}

static void	trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

/*
Used in XXXX().

Updates a HEREDOC token to REDIR_IN and changes the lexeme of the next token
to the created heredoc file.

This converts '<< EOF' into '< heredoc-file', where 'EOF' is replaced by the
actual file created for the heredoc.
*/
static void	update_current_and_next_token(t_token *current_token,
	t_token *next_token, char *heredoc)
{
	current_token->type = REDIR_IN;
	free(next_token->lexeme);
	next_token->lexeme = ft_strdup(heredoc);
	if (!next_token->lexeme)
	{
		print_err_msg(ERR_MALLOC);
		/// THINK OF STH HERE!
	}
}

void	print_heredoc_found(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	t_token *next_token;
	char	*input_line;
	int		fd;
	char	*heredoc;

	current_node = data->tok.tok_lst;
	while (current_node != NULL) // traverse the token list
	{
		current_token = (t_token *)current_node->content;
		count_pipes(data, current_token); // increase pipe counter if token is 'PIPE'
		if (current_token->type == HEREDOC)
		{
		 	next_token = (t_token *)current_node->next->content; // Delimiter is the token after the HEREDOC token.
			heredoc = ft_itoa(data->pipe_nr);
			if (!heredoc)
			{
				print_err_msg(ERR_CREATE_HEREDOC);
				break ;
			}
			fd = open(heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd < 0)
			{
				print_err_msg(ERR_CREATE_HEREDOC);
				free(heredoc);
				break ;
			}
			ft_printf(HEREDOC_P); // weirdly enough, printf() 'lags' here, thus ft_printf() is used
			input_line = get_next_line(0);	// Use get_next_line to read input from stdin (fd = 0)
			trim_newline(input_line);
			while (input_line != NULL && ft_strcmp(input_line, next_token->lexeme) != 0)
			{
				write(fd, input_line, ft_strlen(input_line));
				write(fd, "\n", 1);
				free(input_line);
				ft_printf(HEREDOC_P);
				input_line = get_next_line(0); // Read input again
				trim_newline(input_line);
			}
			if (input_line)
				free(input_line);
			close(fd);
			update_current_and_next_token(current_token, next_token, heredoc);
			free(heredoc);
		}
		current_node = current_node->next;
	}
}
