/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/26 18:06:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains utility functions used throughout the minishell project.
*/

#include "minishell.h"

// IN FILE:

int		is_whitespace(int c);
void	print_err_msg(char *msg);

/*
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.

Returns:
- 1 if character is a whitespace character.
- 0 otherwise.
*/
int	is_whitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

void	print_err_msg(char *msg)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	perror(msg);
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
