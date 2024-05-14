/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:49:28 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/14 17:40:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.
*/
int	ft_isspace(int c)
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
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
// Checks if a character is an arithmetic operator.
// */
// static int	is_math_operator(const char c)
// {
// 	if (c == '+' || c == '-' || c == '*'
// 		|| c == '/' || c == '^' || c == '%')
// 		return (1);
// 	else
// 		return (0);
// }

// /*
// Checks if a character is a delimiter during lexical analysis:
// whitespace, arithmetic operator, redirection symbols (<, >), pipe (|),
// variable expansion ($), single/double quote (' or "), comment symbol (#),
// or a null terminator ('\0').
// */
// static int	is_delimiter(const char c)
// {
// 	if (ft_isspace(c) || is_math_operator(c) || c == '>' || c == '<' || c == '|'
// 		|| c == '$' || c == '\'' || c == '"' || c == '#' || c == '\0')
// 		return (1);
// 	else
// 		return (0);
// }

char	**parser(char *input)
{
	char	**tokens;
	int		i;

	i = 0;
	if (is_input_empty(input))
		return (NULL);
	tokens = ft_split(input, ' ');
	if (tokens)
		printf("EXECUTE CMD!\n");
	// while (input[i])
	// {
	// 	printf("EXECUTE CMD!\n");
	// 	i++;
	// }
	free_str_arr(&tokens);
	return (tokens);

}
