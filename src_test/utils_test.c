/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/24 18:16:34 by aschenk          ###   ########.fr       */
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

// /*
// Prints an error message to stderr, frees memory allocated within the
// fdf structure and exits the program.
// */
// void	msg_and_exit(char *msg, t_data *data)
// {
// 	char	*prefixed_msg;

// 	prefixed_msg = ft_strjoin(ERR_PREFIX, msg);
// 	if (!prefixed_msg)
// 		perror_and_exit(ERR_MALLOC, data);
// 	ft_putstr_fd(prefixed_msg, STDERR_FILENO);
// 	free(prefixed_msg);
// 	free_data(data);
// 	exit(EXIT_FAILURE);
// }

// /*
// Prints an error message to stderr via perror(), which also prints the last
// encountered error and frees memory allocated within the fdf structure.
// Then, exits the program.
// */
// void	perror_and_exit(char *msg, t_data *data)
// {
// 	perror(msg);
// 	free_data(data);
// 	exit(EXIT_FAILURE);
// }

// // FOR TESTING!!
// void	print_string_array(char **array)
// {
// 	int	counter;

// 	counter = 1;
// 	while (*array != NULL)
// 	{
// 		printf("token[%d]: %s\n", counter, *array);
// 		counter++;
// 		array++;
// 	}
// }
