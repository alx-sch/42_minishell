/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:04:08 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/29 12:42:05 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.
*/
int	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/*
Checks if the input string represents an empty command, which can be:
- An empty string ("").
- Contains only whitespace characters.
- Contains only a comment ('# COMMENT'), with optional preceding whitespace.
*/
int	is_input_empty(const char *input)
{
	int	i;

	i = 0;

	while (input[i])
	{
		if (!is_space(input[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
Checks if a character is a delimiter during lexical analysis:
whitespace, redirection symbols (<, >), pipe (|),
variable expansion ($), or a null terminator ('\0').
*/
int	is_delimiter(const char c)
{
	if (is_space(c) || c == '>' || c == '<' || c == '|' || c == '$'
		|| c == '\n' || c == '\0' || c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

/*
FOR TESTING ONLY!!
*/
void	print_token(const t_list *current)
{
	t_token	*token;

	token = (t_token *)(current)->content;
	printf("token type :%u, lexeme: %s position %d", token->type, token->lexeme,
		token->position);
	return ;
}

/*
FOR TESTING ONLY!!
*/
void	print_token_list(t_list *token_list)
{
	t_list	*current;

	current = token_list;
	while (current != NULL)
	{
		print_token(current);
		current = current->next;
	}
	return ;
}
