/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:49:28 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/08 19:51:22 by aschenk          ###   ########.fr       */
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
int	is_command_empty(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '#')
			break ;
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}


/*
Checks if a character is an arithmetic operator.
*/
static bool	is_math_operator(const char c)
{
	if (c == '\0')
		return (false);
	return (c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '^' || c == '%');
}

/*
Checks if a character is a delimiter during lexical analysis:
whitespace, arithmetic operator, redirection symbols (<, >), pipe (|),
variable expansion ($), single/double quote (' or "), comment symbol (#),
or a null terminator ('\0').
*/
static bool	is_delimiter(const char c)
{
	if (ft_isspace(c) || is_math_operator(c) || c == '>' || c == '<' || c == '|'
		|| c == '$' || c == '\'' || c == '"' || c == '#' || c == '\0')
		return (true);
	return (false);
}


// arguments here in case we want to implement the non-interactive mode
// (pass file with commands insteads via CLI)
// int	tokenizer(int argc, char **argv)
// {
// 	char	*input;

// 	(void)argc;
// 	(void)argv;
// 	input = readline(PROMPT);
// 	while (input != NULL)
// 	{
// 		if (ft_strcmp(input, "") != 0)
// 		{

// 		}
// 		free(input);
// 	}
// }
