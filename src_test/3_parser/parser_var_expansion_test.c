/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:40:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/05 19:17:38 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains functions for expanding environment variables within strings.
It provides utilities to identify variables, extract their names, and replace
them with corresponding values from the environment.
*/

#include "minishell.h"

// IN FILE:

int	expand_variables(char **str, t_data *data);

/**
Used in expand_variables().

Checks if a valid variable is encountered at position `i` in the string `str`.
A valid variable is identified by a '$' character that is not followed by
whitespace, the null terminator, or another '$' character.

 @return	`1` if a valid variable is encountered.
			`0` if no valid variable is encountered.
*/
static int	is_variable(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] != '\0' && is_whitespace(str[i + 1]) != 1
		&& str[i + 1] != '$') // '$$' is a special variable not considered, thus not interpreted as variable (is escaped)
		return (1);
	else
		return (0);
}

/**
Used in expand_variables().

This function extracts the variable name following a '$' character.
Variable names are delimited by:
- Whitespace or the null terminator
- Another '$' character
- The '?' character

If the variable is the special case '$?', the function returns a string
containing "?".

 @param str 	The string from which to extract the variable name.
 @param i 		The position in the string where the '$' character is located.

 @return	A newly allocated string containing the variable name
 			(excluding the '$').
			`NULL` if memory allocation fails.
*/
static char	*get_var_name(char *str, int i)
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

/**
Used in replace_var_with_val().

Extracts the value of a specified environment variable (`env_var_search`)
from the minishell-specific environment variables linked list (t_env).
Also extracts the last exit status for '$?'.

 @return	The value the environment variable, if found.
			An empty string, if the specified environment variable is not found.
			`NULL` if memory allocation for the empty or exit status string failed.

If an exit status string is returned, it is the user's responsibilty to
free it when done using.
*/
static char	*get_env_value(const char *var_name, t_data *data)
{
	t_env	*current_node;
	char	*exit_status;
	char	*empty_str;

	current_node = data->envp_temp;
	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_status = ft_itoa(data->exit_status);
		return (exit_status);
	}
	while (current_node) // traverse the minishell-specific environment var list
	{
		if (ft_strcmp(var_name, current_node->e_var) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	empty_str = ft_strdup("");
	if (!empty_str)
		return (NULL);
	return (empty_str);
}

/**
Used in expand_variables().

Replaces the variable at the specified position in the string with its value
from the environment list.

This function locates the variable name in the string starting from position
`i`, retrieves the corresponding value from the environment list, and replaces
the variable in the string with its value. The string is split into three parts:
the left part before the variable, the variable value, and the right part
after the variable. These parts are then concatenated into a new string.

 @param str 		The original string containing the variable to be replaced.
 @param i 			The position in the string where the '$' character of the variable
 					is located.
 @param var_name 	The name of the variable to be replaced (excluding the '$').
 @param env_list 	The environment list containing variable names and their
 					corresponding values.

 @return	`1` if the variable was successfully replaced with its value.
			`0` if an error occurred during memory allocation or if the variable
			does not exist in the environment list.
 */
static int	replace_var_with_val(char **str, int i, char *var_name,
		t_data *data)
{
	char	*var_val;
	char	*str_l;
	char	*str_r;

	str_l = NULL;
	str_r = NULL;
	var_val = get_env_value(var_name, data);
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
	free_vars(&var_val, &str_l, &str_r);
	if (ft_strcmp(var_name, "?") == 0) // free strin allocated for exit status
		free(var_val);
	return (1);
}

/**
Expands all environment variables in the given string with their corresponding
values from the environment list.

This function traverses the input string, identifies variables starting with
a '$' character, and replaces each variable with its corresponding value from the
environment list. If a variable is encountered and successfully replaced, the
function resets the traversal index to handle nested variables by re-traversing
the newly modified string from the beginning. The function stops if a memory
allocation error occurs.

 @param str 		A pointer to the original string containing variables
 					to be expanded.
 @param env_list 	The environment list containing variable names and their
 					corresponding values.

 @return	`1` if all variables were successfully expanded.
			`0` if an error occurred during memory allocation or if no string was passed.
 */
int	expand_variables(char **str, t_data *data)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while ((*str)[i]) // traverse the string
	{
		if (is_variable(*str, i)) // is str[i] start of valid variable? if so, continue.
		{
			var_name = get_var_name(*str, i); // get the variable name
			if (!var_name || !replace_var_with_val(str, i, var_name, data))
			{
				free(var_name);
				return (0); // malloc fail in get_var_name
			}
			free(var_name);
			i = -1; // reset index to traverse the newly expanded string from start again (to also expand nested variables)
		}
		i++;
	}
	return (1);
}
