/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirection_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:00:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/20 21:30:52 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for a redirection
and creates the corresponding token if the redirection is valid.
Returns an error if the redirection is not valid.
*/

#include "minishell.h"

// FUNCTION IN FILE

int	is_redirection(t_data *data, int *i);

/*
Scans the 'input' string starting from the current index (*i).
Skips any leading whitespace and checks if the encountered character is valid.
- Valid redirections are: '>', '>>', '<', '<<'.
- Redirection cannot be the last part of the command line input,
  a valid operand is needed.
- Valid operands cannot be or start with '>', '<', or '|'.

Parameters:
- inp: The input string containing the command line input.
- i: Pointer to the current index in the input string.

Returns:
- Pointer to the dynamically allocated string containing the invalid operand,
  if encountered.
- NULL if the operand is valid or if memory allocation for the invalid
  operand failed.
*/
static char	*is_valid_operand(const char *inp, int *i)
{
	int		j; // index to traverse the input string starting from *i
	char	*invalid_op; // dynamically allocated string to store the invalid operand

	j = *i;
	invalid_op = NULL;
	while (is_space(inp[j])) // Skip leading whitespace
		j++;
	// Check for invalid operands or end of input string (expecting a file)
	if (inp[j] == '>' || inp[j] == '<' || inp[j] == '|' || inp[j] == '\0')
	{
		// Allocate memory for the invalid operand string
		invalid_op = malloc(sizeof(char) * 8); // Allocate for "newline" + null terminator
		if (!invalid_op)
		{
			perror(ERR_MALLOC);
			return (NULL);
		}
		// Construct the invalid operand string
		if (inp[j] == '\0')
			ft_strlcpy(invalid_op, "newline", 8);
		else
		{
			invalid_op[0] = inp[j]; // Invalid operand is the encountered char
			invalid_op[1] = '\0';
		}
		return (invalid_op); // Invalid operand (str) or NULL if malloc failed
	}
	return (NULL); // Valid operand was encountered
}

static void	print_redir_err_msg(char *invalid_op, const char *input,
	char *str_j, int j)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO); // Following output is all in defined ERROR COLOR
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_REDIR_OPERAND, STDERR_FILENO);
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
	ft_putstr_fd(RESET, STDERR_FILENO); // Resets output style to default
}

/*
Checks if the operand in the 'input' string is valid starting from the index *i.
If an invalid operand is found, it prints a custom error message.

Parameters:
- input: The input string containing the command line input.
- i: Pointer to the current index in the input string.
- j: Pointer to the index of the redirection operator in the input string.

Returns:
- 0: If an invalid operand is found and an error message is printed.
- 1: If the operand is valid.
*/
static int	check_operand(const char *input, int *i, int *j)
{
	char	*invalid_op; // String for the invalid operand
	char	*str_j; // String to hold the position of failed redirection

	invalid_op = is_valid_operand(input, i); // Check if the operand is valid
	if (invalid_op) // If an invalid operand is found
	{
		str_j = ft_itoa(*j);
		if (!str_j)
		{
			perror(ERR_MALLOC);
			return (0); // Malloc allocation failure
		}
		print_redir_err_msg(invalid_op, input, str_j, *j);
		free(invalid_op);
		free(str_j);
		return (0); // Invalid operand was found
	}
	return (1); // Operand is valid
}

/*
Function to create redirection tokens and add them to the token list.

Parameters:
- data: Data structure containing input string and token list.
- i: The current index in the input string.
- type: The type of redirection token to be created.
- symbol: The string representation of the redirection symbol.

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
Checks for redirection operators in the 'input' string startinf from index *i.
If a redirection operator is found, it creates the corresponding token and adds
it to the token list. It also checks for a valid operand after the
redirection operator.

Parameters:
- data:	Data structure containing input string and token list.
- i:	The current index in the input string.

Returns:
- 0: If an invalid operand is found or if token creation failed.
- 1: If the redirection and its operand are valid or if no redirection is found.
*/
int	is_redirection(t_data *data, int *i)
{
	int	j;
	int	token_created; // Flag to indicate status of token creation

	j = *i; // Store the initial index value
	// Check for different redirection operators and create corresponding tokens
	if (data->input[*i] == '>' && data->input[*i + 1] == '>')
		token_created = create_redirection_token(data, i, APPEND_OUT, ">>");
	else if (data->input[*i] == '>')
		token_created = create_redirection_token(data, i, REDIR_OUT, ">");
	else if (data->input[*i] == '<' && data->input[*i + 1] == '<')
		token_created = create_redirection_token(data, i, HEREDOC, "<<");
	else if (data->input[*i] == '<')
		token_created = create_redirection_token(data, i, REDIR_IN, "<");
	// Check if a redirection was found and validate its operand
	if (j != *i) // If *i has been incremented, it means a redirection was found
	{
		if (!check_operand(data->input, i, &j) || token_created == 0)
			return (0); // The operand is invalid or token creation failed.
	}
	return (1); // No redirection found or operand is valid
}
