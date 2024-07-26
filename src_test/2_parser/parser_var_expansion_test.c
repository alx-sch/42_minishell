/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:40:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/26 23:04:32 by aschenk          ###   ########.fr       */
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
			printf("length of value: %ld\n", get_env_value_length(env_var_search, env_list));
			return (current_node->value);
		}
		current_node = current_node->next;
	}
	return (NULL);
}

char	*expand_variables(char *str, t_env *env_list) //
{
	char		*expanded;
	int			expanded_len;
	const char	*ptr;
	const char	*var_start;
	const char	*var_end;
	size_t		var_len;
	char		var_name[MAX_VAR_NAME];
	char		*var_value;


	//free(next_token->lexeme);
	//next_token->lexeme = ft_strdup(heredoc);

	expanded = malloc(ft_strlen(str) + 1); // Allocate mmeory for expanded str
	if (!expanded)
	{
		perror(ERR_MALLOC);
		return (NULL);
	}
	expanded_len = 0;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == '$' && *(ptr + 1) != '\0')
		{
			var_start = ptr + 1; // Pointer to the start of variable name
			var_end = var_start; // Pointer to the end of variable name (initialziation)
			// Find the end of the variable name
			while (*var_end != '\0' && (ft_isalnum(*var_end) || *var_end == '_'))
				var_end++;
			var_len = var_end - var_start;
			ft_strlcpy(var_name, var_start, var_len + 1);
			var_value = get_env_value(var_name, env_list);
			if (var_value != NULL) {
				printf("var value of '%s': %s\n", var_name, var_value);
			} else {
				printf("var %s not found in environment\n", var_name);
			}
			ptr = var_end;
		}
		else
			expanded[expanded_len++] = *ptr++;
	}
	expanded[expanded_len] = '\0';
	return (expanded);
}
