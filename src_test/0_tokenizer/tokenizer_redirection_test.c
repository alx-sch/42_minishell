/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirection_test.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:00:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/17 18:18:36 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for a valid redirection.
*/

#include "minishell.h"

// FILE

int	is_redirection(t_list **lst, const char *input, int *i);

/*
Scans the 'input' string starting from the current index (*i).
Skips any leading whitespace and checks if the encountered character is valid.
- Valid redirections are: '>', '>>', '<', '<<'.
- Redirection cannot be the last part of the command line input,
  a valid operand is needed.
- Valid operands cannot be or start with '>', '<', or '|'.

Parameters:
- input: The input string containing the command line input.
- *i: Pointer to the current index in the input string.

Returns:
- the invalid operand (char *); if invalid operand was ecountered.
- NULL; if operand is valid or malloc for invalid operand failed.
*/
static char	*is_valid_operand(const char *input, int *i)
{
	int		j; // index to traverse the input string starting from *i
	char	*invalid_op; // dynamically allocated string to store the invalid operand
	char	char_str[2]; // temp. buffer to hold a single character operand and null terminator

	j = *i;
	invalid_op = NULL;
	while (is_space(input[j])) // skipping whitespace
		j++;
	if (input[j] == '>' || input[j] == '<' || input[j] == '|'
		|| input[j] == '\0') // invalid operands / EOF
	{
		if (input[j] == '\0')
			invalid_op = ft_strdup("newline"); // it's 'newline' as bash adds '\n' to input string
		else
		{
			char_str[0] = input[j]; //invalid operand is encountered char
			char_str[1] = '\0';
			invalid_op = ft_strdup(char_str);
		}
		if (!invalid_op)
			perror(ERR_MALLOC);
		return (invalid_op); // invalid operand (str) or NULL if malloc failed
	}
	else
		return (NULL); // valid operand was encountered
}

/*
Checks if the operand in the 'input' string is valid starting from the index *i.
If an invalid operand is found, it prints a custom error message.

Parameters:
- input: The input string containing the command line input.
- i: Pointer to the current index in the input string.
- j: Pointer to the index of the redirection operator in the input string.

Returns:
- 0; if an invalid operand is found and an error message is printed.
- 1; if the operand is valid.
*/
static int	check_operand(const char *input, int *i, int *j)
{
	char	*invalid_op; // Pointer to store the invalid operand string

	invalid_op = is_valid_operand(input, i); // Check if the operand is valid
	if (invalid_op) // If an invalid operand is found
	{
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
		return (0); // invalid operand was found
	}
	return (1); // operand is valid
}

/*
Checks if the current part of the 'input' string starting from index *i is a
redirection operator.
If a redirection operator is found, it adds the corresponding token to a list
and checks for a valid operand.

Parameters:
- lst: Pointer to the list where tokens are added.
- input: The input string containing the command line input.
- i: Pointer to the current index in the input string.

Returns:
- 0 if an invalid operand is found.
- 1 if the redirection and its operand are valid or if no redirection is found.
*/
int	is_redirection(t_list **lst, const char *input, int *i)
{
	int	j; // Local index to keep track of the initial position

	j = *i; // Store the initial index value
	if (input[*i] == '>' && input[*i + 1] == '>')
		ft_lstadd_back(lst, create_token(APPEND_OUT, ">>", i)); // Append output redirection (>>)
	else if (input[*i] == '>')
		ft_lstadd_back(lst, create_token(REDIRECT_OUT, ">", i)); // Output redirection (>)
	else if (input[*i] == '<' && input[*i + 1] == '<')
		ft_lstadd_back(lst, create_token(HEREDOC, "<<", i)); // Heredoc redirection (<<)
	else if (input[*i] == '<')
		ft_lstadd_back(lst, create_token(REDIRECT_IN, "<", i)); // Input redirection (<)
	if (j != *i) // If *i has been incremented, it means a redirection was found
		if (!check_operand(input, i, &j)) // Check the operand after the redirection operator
			return (0); // Return 0 if the operand is invalid
	return (1); // Return 1 if the redirection and its operand are valid or if no redirection is found
}
