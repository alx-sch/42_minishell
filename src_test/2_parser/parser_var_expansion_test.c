/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:40:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/27 13:07:39 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

/*
Used in XXX().

Returns:
- The value length of the specified environmental variable, if found.
- '0' if the specified environmental variable is not found.
*/
static size_t	get_env_value_length(const char *env_var_search,
	t_env *env_node)
{
	t_env	*current_node;
	size_t	val_length;

	current_node = env_node;
	while (current_node)
	{
		if (ft_strcmp(env_var_search, current_node->e_var) == 0)
		{
			if (current_node->value)
			{
				val_length = ft_strlen(current_node->value);
				return (val_length);
			}
		}
		current_node = current_node->next;
	}
	return (0);
}

/*
Used in XXX().

Extracts the value of a specified environment variable ('env_var_search')
from the minishell-specific environmental variables linked list (t_env).

Returns:
- The value the environmental variable, if found.
- NULL if the specified environmental variable is not found.
*/
static char	*get_env_value(const char *env_var_search, t_env *env_list)
{
	t_env	*current_node;

	current_node = env_list;
	while (current_node)
	{
		if (ft_strcmp(env_var_search, current_node->e_var) == 0)
		{
			printf("length of value: %ld\n", get_env_value_length(env_var_search, env_list)); // TEST ONLY
			return (current_node->value);
		}
		current_node = current_node->next;
	}
	return (NULL);
}
/*
Checks if a valid variable is encountered at position `i` in the string `str`.
A valid variable is identified by a '$' character that is not followed by:
- whitespace or null terminator
- another '$' character

Returns:
- 1 if a valid variable is encountered at position `i`.
- 0 if no valid variable is encountered at position `i`.
*/
int	is_variable(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] != '\0' && is_whitespace(str[i + 1]) != 1
		&& str[i + 1] != '$') // '$$' is a special variable not considered, thus not interpreted as variable (is escaped)
		return (1);
	else
		return (0);
}

/*
This function extracts the variable name following a '$' character.
Variable names are delimited by:
- Whitespace or the null terminator
- Another '$' character
- The '?' character

If the variable is the special case '$?', the function returns a string
containing "?".

Parameters:
- str: The string from which to extract the variable name.
- i: The position in the string where the '$' character is located.

Returns:
- A newly allocated string containing the variable name (excluding the '$').
- NULL if memory allocation fails.
*/
char	*get_var_name(char *str, int i)
{
	const char	*var_start;
	const char	*var_end;
	size_t		var_len;
	char		*var_name;

	var_start = &str[i + 1]; // move past the '$' sign
	if (*var_start == '?') // is special variable 'exit status'
	{
		var_name = ft_strdup("?");
		return (var_name);
	}
	var_end = var_start;
	while (*var_end && !is_whitespace(*var_end) && *var_end != '$'
		&& *var_end != '?')
		var_end++; // find the end of the variable name
	var_len = var_end - var_start;
	var_name = malloc(var_len + 1); // +1 for null terminator
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, var_start, var_len + 1);
	return (var_name);
}

int	expand_first_variable(char **str, t_env *env_list)
{
	char		*var_name;
	int	i;

	get_env_value("", env_list);
	i = 0;
	(void)i;

	printf("input: %s\n", *str);
	while ((*str)[i])
	{
		if (is_variable(*str, i))
		{
			var_name = get_var_name(*str, i);
			if (!var_name)
				print_err_msg(ERR_VAR_EXP);
			else
			{
				printf("var name: %s\n", var_name);
				free(var_name);
			}
			free(*str);
			*str = ft_strdup("YES");
			break ;
		}
		i++;
	}
	printf("input: %s\n", *str);

	return (1);
}
