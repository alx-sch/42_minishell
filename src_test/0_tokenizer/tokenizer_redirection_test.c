/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirection_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:00:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/18 16:18:05 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for a valid redirection.
*/

#include "minishell.h"

// FILE

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
	// Check for invalid operands or end of input string
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
	char	*invalid_op; // Pointer to store the invalid operand string

	invalid_op = is_valid_operand(input, i); // Check if the operand is valid
	if (invalid_op) // If an invalid operand is found
	{
		// Print error message
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd(ERR_REDIR_OPERAND, STDERR_FILENO);
		if (input[*j] == '>' && input[*j + 1] == '>')
			ft_putstr_fd("'>>': '", STDERR_FILENO);
		else if (input[*j] == '>')
			ft_putstr_fd("'>': '", STDERR_FILENO);
		else if (input[*j] == '<' && input[*j + 1] == '<')
			ft_putstr_fd("'<<': '", STDERR_FILENO);
		else if (input[*j] == '<')
			ft_putstr_fd("'<': '", STDERR_FILENO);
		ft_putstr_fd(invalid_op, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		free(invalid_op);
		return (0); // Invalid operand was found
	}
	return (1); // Operand is valid
}

// Function to create redirection tokens and add them to the token list.
static void	create_redirection_token(t_data *data, int *i, t_token_type type,
	const char *symbol)
{
	data->tok.new_node = create_tok(data, type, symbol, i);
	// Update the position pointer if token creation fails (as this is done when create_tok() is successful)
	if (!data->tok.new_node)
		*i = *i + ft_strlen(symbol);
	else
		ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node);
}

/*
Checks for redirection operators in the 'input' string starting from index *i.
If a redirection operator is found, it creates the corresponding token and adds
it to the token list.
It also checks for a valid operand after the redirection operator.

Parameters:
- data:	Data structure containing input string and token list.
- i:	The current index in the input string.

Returns:
- 0: If an invalid operand is found.
- 1: If the redirection and its operand are valid or if no redirection is found.
*/
int	is_redirection(t_data *data, int *i)
{
	int	j;

	j = *i; // Store the initial index value
	// Check for different redirection operators and create corresponding tokens
	if (data->input[*i] == '>' && data->input[*i + 1] == '>')
		create_redirection_token(data, i, APPEND_OUT, ">>");
	else if (data->input[*i] == '>')
		create_redirection_token(data, i, REDIRECT_OUT, ">");
	else if (data->input[*i] == '<' && data->input[*i + 1] == '<')
		create_redirection_token(data, i, HEREDOC, "<<");
	else if (data->input[*i] == '<')
		create_redirection_token(data, i, REDIRECT_IN, "<");
	// Check if a redirection was found and validate its operand
	if (j != *i) // If *i has been incremented, it means a redirection was found
		if (!check_operand(data->input, i, &j))
			return (0); // The operand is invalid
	return (1); // No redirection found or operand is valid
}
