/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotation_test.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:36:32 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/25 21:26:54 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// Function to create redirection tokens and add them to the token list.
static void	create_quotation_token(t_data *data, int *i, t_token_type type,
	const char *symbol)
{
	data->tok.new_node = create_tok(data, type, symbol, i);
	// Update the position pointer if token creation fails (as this is done when create_tok() is successful)
	if (!data->tok.new_node)
		*i = *i + ft_strlen(symbol);
	else
		ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node);
}

static int	is_closed(t_data *data, int *i, const char c)
{
	char	char_str[2]; // String to hold char c and null terminator
	int		j;

	j = *i + 1; // Go to position after opening char (e.g., quotation mark)
	while (data->input[j])
	{
		if (data->input[j] == c)
		{

			return (1); // char is closed
		}
		j += 1;
	}
	char_str[0] = c;
	char_str[1] = '\0';
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_PRE, STDERR_FILENO);
	ft_putstr_fd(char_str, STDERR_FILENO);
	ft_putstr_fd(ERR_NOT_CLOSED_SUF, STDERR_FILENO);
	return (0); // char (e.g. quotation mark) is not closed
}

int	is_single_quotation(t_data *data, int *i)
{
	//int	j;

	//j = *i; // Store the initial index value
	if (data->input[*i] == '\'')
		if (!is_closed(data, i, '\''))
			return (0); // not closed

	if (data->input[*i] == '\"')
		if (!is_closed(data, i, '\"'))
			return (0); // not closed
	return (1); // no quotation found or is closed
}


