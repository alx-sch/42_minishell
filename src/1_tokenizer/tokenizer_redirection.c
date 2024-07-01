/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:00:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 19:08:23 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for redirections
and creates the corresponding token if the redirection points to valid operand.

Returns an error message if the redirection is not valid.
*/

#include "minishell.h"

// IN FILE:

int	is_redirection(t_data *data, int *i);

/*
Used in check_operand().

Scans the input string starting from the current index (*i).
Skips any leading whitespace and checks if the encountered character is valid.
- Valid redirections are: '>', '>>', '<', '<<'.
- Redirection cannot be the last part of the input string,
  a valid operand is needed.
- Valid operands (files) cannot be or start with '>', '<', or '|'.

Parameters:
- char *inp: The input string containing the command line input.
- int *i: The current index in the input string.

Returns:
- The dynamically allocated string containing the invalid operand.
- NULL if the operand is valid
- "ERR" string literal, if memory allocation fails while attempting to
  allocate space for the invalid operand.
*/
static char	*is_valid_operand(const char *inp, int *i)
{
	int		j;
	char	*invalid_op;

	j = *i;
	invalid_op = NULL;
	while (is_whitespace(inp[j]))
		j++;
	if (inp[j] == '>' || inp[j] == '<' || inp[j] == '|' || inp[j] == '\0')
	{
		invalid_op = malloc(sizeof(char) * 8);
		if (!invalid_op)
		{
			perror(ERR_MALLOC);
			return ("ERR");
		}
		if (inp[j] == '\0')
			ft_strlcpy(invalid_op, "newline", 8);
		else
		{
			invalid_op[0] = inp[j];
			invalid_op[1] = '\0';
		}
		return (invalid_op);
	}
	return (NULL);
}

/*
Used in check_operand().

Prints an error message for invalid redirection operands in the input string.

Parameters:
- char *invalid_op:		The invalid operand encountered in the input.
- const char *input:	The  input string containing the command line input.
- char *str_j:	The string representation of int j.
- int j: 		Position index of the failed redirection in the input string.
*/
static void	print_redir_err_msg(char *invalid_op, const char *input,
	char *str_j, int j)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
	if (input[j] == '>' && input[j + 1] == '>')
		ft_putstr_fd("'>>': '", STDERR_FILENO);
	else if (input[j] == '>')
		ft_putstr_fd("'>': '", STDERR_FILENO);
	else if (input[j] == '<' && input[j + 1] == '<')
		ft_putstr_fd("'<<': '", STDERR_FILENO);
	else if (input[j] == '<')
		ft_putstr_fd("'<': '", STDERR_FILENO);
	ft_putstr_fd(invalid_op, STDERR_FILENO);
	ft_putstr_fd("' (position: ", STDERR_FILENO);
	ft_putstr_fd(str_j, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

/*
Used in is_redirection().

Checks if the operand in the 'input' string is valid starting from the index *i.
If an invalid operand is found, it prints a custom error message.

Parameters:
- char *input: The input string containing the command line input.
- int *i:	Pointer to the current index in the input string.
- int j:	The index of the redirection operator in the input string.

Returns:
- 0: If an invalid operand is found and an error message is printed.
- 1: If the operand is valid.
*/
static int	check_operand(const char *input, int *i, int j)
{
	char	*invalid_op;
	char	*str_j;

	invalid_op = is_valid_operand(input, i);
	if (invalid_op)
	{
		str_j = ft_itoa(j);
		if (!str_j)
		{
			perror(ERR_MALLOC);
			return (0);
		}
		print_redir_err_msg(invalid_op, input, str_j, j);
		free(invalid_op);
		free(str_j);
		return (0);
	}
	return (1);
}

/*
Used in is_redirection().

Function to create redirection tokens and add them to the token list.

Parameters:
- t_data *data:	Data structure containing input string and token list.
- int *i:		Pointer to the current index in the input string.
- t_token_type type:	The type of redirection token to be created.
- char *symbol:	The string representation of the redirection symbol.

Returns:
- 0 if the token creation failed.
- 1 if the token creation was successful.
*/
static int	create_redirection_token(t_data *data, int *i, t_token_type type,
	const char *symbol)
{
	data->tok.new_node = create_tok(data, type, symbol, i);
	if (data->tok.new_node == NULL)
		return (0);
	ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node);
	return (1);
}

/*
Checks for redirection operators in the 'input' string starting from index *i.
If a redirection operator is found, it creates the corresponding token and adds
it to the token list. It also checks for a valid operand (file) after the
redirection operator.

Parameters:
- t_data *data:	Data structure containing input string and token list.
- int *i:		Pointer to the current index in the input string.

Returns:
- 0 if an invalid operand is found or if token creation failed.
- 1 if the redirection and its operand are valid or if no redirection is found.
*/
int	is_redirection(t_data *data, int *i)
{
	int	j;
	int	token_created;

	j = *i;
	if (data->input[*i] == '>' && data->input[*i + 1] == '>')
		token_created = create_redirection_token(data, i, APPEND_OUT, ">>");
	else if (data->input[*i] == '>')
		token_created = create_redirection_token(data, i, REDIR_OUT, ">");
	else if (data->input[*i] == '<' && data->input[*i + 1] == '<')
		token_created = create_redirection_token(data, i, HEREDOC, "<<");
	else if (data->input[*i] == '<')
		token_created = create_redirection_token(data, i, REDIR_IN, "<");
	if (j != *i)
	{
		if (!check_operand(data->input, i, j) || token_created == 0)
			return (0);
	}
	return (1);
}
