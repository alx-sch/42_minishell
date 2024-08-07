/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/07 20:23:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains utility functions used throughout the minishell project,
including functions for character classification and error message printing.
*/

#include "minishell.h"

// IN FILE:

int		is_whitespace(int c);
int		contains_quotes(const char *str);
void	print_err_msg(char *msg);
void	print_err_msg_prefix(char *msg);
void	print_err_msg_custom(char *msg, unsigned int print_newline);

/**
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.

 @param c The character to check.

 @return	`1` if the character is one of the whitespace characters.
 			`0` otherwise.
*/
int	is_whitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/**
Checks if a string contains either single or double quotes.

 @param str 	The string to be checked.

 @return		`1` if the string contains at least one single or double quote.
				`0` otherwise.
*/
int	contains_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

/**
Prints an error message to the standard error stream (stderr),
with additional formatting applied.
The actual error description is obtained using `perror`, which
appends a system-generated message based on the current `errno`.

 @param msg 	The error message to be printed. This should be a
				descriptive string about the error that occurred.
*/
void	print_err_msg(char *msg)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	perror(msg);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
}

/**
Prints formatted error message with leading ERR_PREFIX.
The actual error description is obtained using `perror`, which
appends a system-generated message based on the current `errno`.

 @param msg 	The error message to be printed. This should be a
				descriptive string about the error that occurred.
*/
void	print_err_msg_prefix(char *msg)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	perror(msg);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
}

/**
Prints an error message to the standard error stream (stderr),
with additional formatting applied. Prints custom error messages
not covered by an errno, thus does not use perror().

 @param msg 			The error message to be printed. This should be a
						descriptive string about the error that occurred.
 @param print_newline 	Flag to print the newline character after
						the error message (`0` does not, otherwise does).
*/
void	print_err_msg_custom(char *msg, unsigned int print_newline)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (print_newline)
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
}

// Function to print the list of tokens
// FOR TESTING ONLY; use `print_token_list(data.tok.tok_lst)` in main().
void	print_token_list(t_list *lst)
{
	while (lst)
	{
		t_token *token = lst->content;
		printf("Position[%d]: '%s' (token type: %d)\n", token->position, token->lexeme, token->type);
		lst = lst->next;
	}
}
