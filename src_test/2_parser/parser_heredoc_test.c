/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/25 17:53:41 by aschenk          ###   ########.fr       */
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

void	print_heredoc_found(t_data *data)
{
	t_list	*current_node;
	t_token	*current_token;
	char	*input_line;
	char	*heredoc_delim;
	int		fd;
	char	*heredoc;

	current_node = data->tok.tok_lst;
	while (current_node != NULL) // traverse the token list
	{
		current_token = (t_token *)current_node->content;
		count_pipes(data, current_token); // increase pipe counter if token is 'PIPE'
		if (current_token->type == HEREDOC)
		{
		 	heredoc_delim = ((t_token *)current_node->next->content)->lexeme; // Delimiter is the token after the HEREDOC token.
			heredoc = ft_itoa(data->pipe_nr);
			fd = open(heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			free(heredoc);
            if (fd < 0)
            {
                perror("Failed to open file");
                return;
            }
			ft_printf(HEREDOC_P); // weirdly enough, printf() 'lags' here, thus ft_printf() is used
			input_line = get_next_line(0);	// Use get_next_line to read input from stdin (fd = 0)
			trim_newline(input_line);
			while (input_line != NULL && ft_strcmp(input_line, heredoc_delim) != 0)
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
		}
		current_node = current_node->next;
	}
}
