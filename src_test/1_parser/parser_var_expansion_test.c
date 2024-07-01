/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:40:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/27 19:30:24 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

/*
From pipex project.
Extracts the value of a specified environment variable ('env_var_search')
from the given environment variable array ('env').

Returns:
- A pointer to the value part of the environmenta variable, if found.
- NULL if the specified environmental variable is not found in the envp array.
*/
static char	*get_env_values(const char *env_var_search, char **env)
{
	size_t	i;
	size_t	len;
	char	*env_var;

	i = 0;
	while (env[i])
	{
		len = 0;
		while (env[i][len] != '=' && env[i][len])
			len++;
		env_var = ft_substr(env[i], 0, len);
		if (!env_var)
		{
			perror(ERR_MALLOC);
			return (NULL);
		}
		if (ft_strcmp(env_var, env_var_search) == 0)
		{
			free(env_var);
			return (env[i] + len + 1);
		}
		free(env_var);
		i++;
	}
	return (NULL);
}


char	*expand_variables(t_data *data)
{
	char		*expanded;
	int			expanded_len;
	const char	*ptr;
	const char	*var_start;
	const char	*var_end;
	size_t		var_len;
	char		var_name[MAX_VAR_NAME];
	char		*var_value;

	expanded = malloc(ft_strlen(data->input) + 1); // Allocate mmeory for expanded str
	if (!expanded)
	{
		perror(ERR_MALLOC);
		return (NULL);
	}
	expanded_len = 0;
	ptr = data->input;
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
			var_value = get_env_values(var_name, data->envp);
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
