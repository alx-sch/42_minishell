/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_utils_test.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:58:01 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/27 20:01:08 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// IN FILE:

int	get_str_l(char **str, int i, char **substr_left);
int	get_str_r(char **str, int i, char *var_name,
	char **substr_right);
int	join_str_l(char **str, char *str_l, char *var_value);
int	join_str_r(char **str, char *str_r);
void	free_vars(char **var_val, char **str_l, char **str_r);

int	get_str_l(char **str, int i, char **substr_left)
{
	// Substring from the beginning of the string until index i (before the variable name)
	*substr_left = malloc(i + 1);
	if (!*substr_left)
		return (0);
	ft_strlcpy(*substr_left, *str, i + 1);
	return (1);
}

int	get_str_r(char **str, int i, char *var_name,
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

int	join_str_l(char **str, char *str_l, char *var_value)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(str_l, var_value);
	if (!tmp_str)
		return (0); // allocation fails
	free(*str); // free old string (not expanded)
	*str = tmp_str; // assign the new concatenated string to *str
	return (1);
}

int	join_str_r(char **str, char *str_r)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(*str, str_r);
	if (!tmp_str)
		return (0); // allocation fails
	free(*str);
	*str = tmp_str; // assign the new concatenated string to *str
	return (1);
}

void	free_vars(char **var_val, char **str_l, char **str_r)
{
	if (ft_strcmp(*var_val, "") == 0) // if var value is empty, it was dynamically allocated -> needs to be freed
		free(*var_val);
	if (*str_l)
		free(*str_l);
	if (*str_r)
		free(*str_r);
}
