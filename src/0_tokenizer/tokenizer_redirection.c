/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:00:24 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/17 21:07:52 by aschenk          ###   ########.fr       */
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
	int		j;
	char	*invalid_op;
	char	char_str[2];

	j = *i;
	invalid_op = NULL;
	while (is_space(input[j]))
		j++;
	if (input[j] == '>' || input[j] == '<' || input[j] == '|'
		|| input[j] == '\0')
	{
		if (input[j] == '\0')
			invalid_op = ft_strdup("newline");
		else
		{
			char_str[0] = input[j];
			char_str[1] = '\0';
			invalid_op = ft_strdup(char_str);
		}
		if (!invalid_op)
			perror(ERR_MALLOC);
		return (invalid_op);
	}
	else
		return (NULL);
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
	char	*invalid_op;

	invalid_op = is_valid_operand(input, i);
	if (invalid_op)
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
		return (0);
	}
	return (1);
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
	int	j;

	j = *i;
	if (input[*i] == '>' && input[*i + 1] == '>')
		ft_lstadd_back(lst, create_token(APPEND_OUT, ">>", i));
	else if (input[*i] == '>')
		ft_lstadd_back(lst, create_token(REDIRECT_OUT, ">", i));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		ft_lstadd_back(lst, create_token(HEREDOC, "<<", i));
	else if (input[*i] == '<')
		ft_lstadd_back(lst, create_token(REDIRECT_IN, "<", i));
	if (j != *i)
		if (!check_operand(input, i, &j))
			return (0);
	return (1);
}
