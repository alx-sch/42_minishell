/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/31 21:58:25 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains utility functions used throughout the minishell project,
including functions for character classification and error message printing.
*/

#include "minishell.h"

// IN FILE:

int		is_whitespace(int c);
void	print_err_msg(char *msg);
void	print_err_msg_prefix(char *msg);
void	print_err_msg_custom(char *msg);

/**
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.

 @param c The character to check.

 @return `1` if the character is one of the whitespace characters.
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
Prints an error message to the standard error stream (stderr),
with additional formatting applied.
The actual error description is obtained using `perror`, which
appends a system-generated message based on the current `errno`.

 @param msg The error message to be printed. This should be a
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

 @param msg The error message to be printed. This should be a
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

 @param msg The error message to be printed. This should be a
			descriptive string about the error that occurred.
*/
void	print_err_msg_custom(char *msg)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO); // Reset the output style to default
}

// Function to print the list of tokens
// FOR TESTING ONLY
void	print_token_list(t_list *lst)
{
	while (lst)
	{
		t_token *token = lst->content;
		printf("Position[%d]: '%s' (token type: %d)\n", token->position, token->lexeme, token->type);
		lst = lst->next;
	}
}
