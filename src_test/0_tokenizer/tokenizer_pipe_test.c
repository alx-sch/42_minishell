/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pipe_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:34:21 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 18:09:50 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for a pipe symbol ('|')
and creates the corresponding token if the syntax before and after the piping
is valid.

Returns an error message if the piping syntax is not valid.
*/

#include "minishell.h"

// IN FILE:

int	is_pipe(t_data *data, int *i);

/*
Used in check_syntax().
Mostly a simplified version of is_valid_operand() in tokenizer_redirection.c.

Scans the input string starting from the current index (*i).
Skips any leading whitespace and checks if the encountered character is valid.
- Valid syntax after a pipe: Anything but '|' and end of input ('\0').

Parameters:
- char *inp: The input string containing the command line input.
- int *i: The current index in the input string.

Returns:
- The dynamically allocated string containing the invalid syntax symbol
  ('newline' for '\0' to mirror the behavior of invalid redirections).
- NULL if the syntax is valid
- "ERR" string literal, if memory allocation fails while attempting to
  allocate space for the invalid syntax.
*/
static char	*is_valid_syntax(const char *inp, int j)
{
	char	*invalid_syn; // dynamically allocated string to store the invalid syntax symbol

	j += 1;
	invalid_syn = NULL;
	while (is_space(inp[j])) // Skip leading whitespace
		j++;
	// Check for invalid operands or end of input string (expecting a file)
	if (inp[j] == '|' || inp[j] == '\0')
	{
		// Allocate memory for the invalid operand string
		invalid_syn = malloc(sizeof(char) * 8); // Allocate for "newline" + null terminator
		if (!invalid_syn)
			return ("ERR"); // Default invalid operand, if memory allocation failed
		// Construct the invalid operand string
		if (inp[j] == '\0')
			ft_strlcpy(invalid_syn, "newline", 8);
		else
		{
			invalid_syn[0] = inp[j]; // Invalid operand is the encountered char
			invalid_syn[1] = '\0';
		}
		return (invalid_syn); // Invalid operand (str) or NULL if malloc failed
	}
	return (NULL); // Valid syntax was encountered
}

/*
Used in check_syntax().

Prints an error message for invalid syntax encountered after a pipe symbol ('|').

Parameters:
- char *invalid_syn:	The invalid operand encountered in the input.
- char *str_j:			The string representation of int j (position of failed piping).
*/
static void	print_pipe_err_msg(char *invalid_syn, char *str_j)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO); // Set error color for the output
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd("'|': '", STDERR_FILENO);
	ft_putstr_fd(invalid_syn, STDERR_FILENO); // Print the invalid operand
	ft_putstr_fd("' (position: ", STDERR_FILENO);
	ft_putstr_fd(str_j, STDERR_FILENO); // Print the position of failed redirection
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
}

/*
Used in check_syntax().

Prints an error message for missing input before the first pipe ('|').

Parameters:
- char *invalid_syn:	The invalid operand encountered in the input.
- char *str_j:			The string representation of int j (position of failed piping).
*/
static void	print_empty_pipe_err_msg(char *str_j)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO); // Set error color for the output
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_EMPTY_PIPE, STDERR_FILENO);
	ft_putstr_fd(" (position: ", STDERR_FILENO);
	ft_putstr_fd(str_j, STDERR_FILENO); // Print the position of failed redirection
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
}

/*
Used in is_pipe().

Checks if the syntax before/after an encountered '|' valid.
If syntax is invalid, it prints a custom error message.

Parameters:
- t_data *data:    Data structure containing token-related info.
- int j:           The index of the piping symbol ('|').

Returns:
- 0: If syntax is invalid and an error message was printed OR malloc fail.
- 1: If the syntax is valid.
*/
static int	check_syntax(t_data *data, int j)
{
	char	*invalid_syn; // String for the invalid syntax.
	char	*str_j; // String to hold the position of failed piping.


	invalid_syn = is_valid_syntax(data->input, j); // Check if the syntax is valid.
	if (invalid_syn != NULL || data->tok.tok_lst == NULL) // If invalid syntax is found OR if 'pipe' token would be the first token.
	{
		str_j = ft_itoa(j);
		if (!str_j)
		{
			perror(ERR_MALLOC);
			return (0); // Malloc allocation failure
		}
		if (data->tok.tok_lst == NULL)
			print_empty_pipe_err_msg(str_j);
		else
			print_pipe_err_msg(invalid_syn, str_j);
		free(invalid_syn);
		free(str_j);
		return (0); // Invalid syntax was found.
	}
	return (1); // Syntax is valid.
}

/*
If the character at index *i in the input string is a pipe symbol ('|'),
the function checks if the syntax before and after the '|' is valid:
- Input before and after a pipe cannot be empty.
- Note: Our minishell interprets '||' as "empty input between pipes" not as "OR".

If the syntax is valid, it creates the corresponding token and adds
it to the token list.

Parameters:
- t_data *data: Data structure containing input string and token list.
- int *i:       Pointer to the current index in the input string.

Returns:
- 0 if the syntax is invalid or if token creation failed.
- 1 if a pipe token was added to the token list or if no pipe is found.
*/
int	is_pipe(t_data *data, int *i)
{
	int	j;

	if (data->input[*i] == '|')
	{
		j = *i;
		if (check_syntax(data, j))
		{
			data->tok.new_node = create_tok(data, PIPE, "|", i);
			if (data->tok.new_node == NULL)
				return (0); // Token creation failed.
			ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node);
			return (1); // Pipe token added to token list.
		}
		else
			return (0); // Syntax is invalid.
	}
	else
		return (1); // No pipe symbol found.
}
