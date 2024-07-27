/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:40:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/27 20:05:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

/*
Used in XXX().

Extracts the value of a specified environment variable ('env_var_search')
from the minishell-specific environmental variables linked list (t_env).

Returns:
- The value the environmental variable, if found.
- an empty string, if the specified environmental variable is not found.
- NULL if memory allocation for the empty string failed.

If an empty string is returned, it is the user's responsibilty to free it
when done using.
*/
static char	*get_env_value(const char *env_var_search, t_env *env_list)
{
	t_env	*current_node;
	char	*empty_str;

	current_node = env_list;
	while (current_node) // traverse the minishell-specific environmental var list
	{
		if (ft_strcmp(env_var_search, current_node->e_var) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	empty_str = ft_strdup("");
	if (!empty_str)
		return (NULL);
	return (empty_str);
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

static int	get_str_l(char **str, int i, char **substr_left)
{
	// Substring from the beginning of the string until index i (before the variable name)
	*substr_left = malloc(i + 1);
	if (!*substr_left)
		return (0);
	ft_strlcpy(*substr_left, *str, i + 1);
	return (1);
}

static int	get_str_r(char **str, int i, char *var_name,
	char **substr_right)
{
	// Substring from index i + var_value_len (after variable name) to the end of the string
	*substr_right = malloc(ft_strlen(*str) - i - ft_strlen(var_name) + 1);
	if (!*substr_right)
		return (0);
	ft_strlcpy(*substr_right, *str + i + 1 + ft_strlen(var_name),
		strlen(*str) - i - ft_strlen(var_name) + 1);
	return (1);
}

static int	join_str_l(char **str, char *str_l, char *var_value)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(str_l, var_value);
	if (!tmp_str)
		return (0); // allocation fails
	free(*str); // free old string (not expanded)
	*str = tmp_str; // assign the new concatenated string to *str
	return (1);
}

static int	join_str_r(char **str, char *str_r)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(*str, str_r);
	if (!tmp_str)
		return (0); // allocation fails
	free(*str);
	*str = tmp_str; // assign the new concatenated string to *str
	return (1);
}

static void	free_vars(char **var_val, char **str_l, char **str_r)
{
	if (ft_strcmp(*var_val, "") == 0) // if var value is empty, it was dynamically allocated -> needs to be freed
		free(*var_val);
	if (*str_l)
		free(*str_l);
	if (*str_r)
		free(*str_r);
}

int	join_var_value_w_string(char **str, int i, char *var_name, t_env *env_list)
{
	char	*var_val;
	char	*str_l;
	char	*str_r;

	str_l = NULL;
	str_r = NULL;
	var_val = get_env_value(var_name, env_list);
	if (!var_val)
		return (0); // memory allocation for empty string failed.
	if (!get_str_l(str, i, &str_l) || !get_str_r(str, i, var_name, &str_r))
	{
		free_vars(&var_val, &str_l, &str_r);
		return (0); // allocating memory for either the left or right substring failed
	}
	if (!join_str_l(str, str_l, var_val) || !join_str_r(str, str_r))
	{
		free_vars(&var_val, &str_l, &str_r);
		return (0); // allocating memory when joining left or right substring failed
	}


	printf("joined str: '%s'\n", *str);

	free(str_l);
	free(str_r);
	if (ft_strcmp(var_val, "") == 0) // if var value is empty, it was dynamically allocated above -> needs to be freed
		free(var_val);
	return (1);
}


int	expand_first_variable(char **str, t_env *env_list)
{
	char	*var_name;
	int		i;

	i = 0;
	while ((*str)[i]) // traverse the string
	{
		if (is_variable(*str, i)) // is str[i] start of valid variable? if so, continue.
		{
			printf("input: '%s'\n", *str);
			var_name = get_var_name(*str, i); // get the variable name
			if (!var_name)
				return (0); // malloc fail in get_var_name
			if (!join_var_value_w_string(str, i, var_name, env_list))
				print_err_msg(ERR_VAR_EXP);
			free(var_name);
			break ; // stop traversing the string once the first variable is expanded
		}
		i++;
	}
	printf("input: %s\n", *str);

	return (1);
}
