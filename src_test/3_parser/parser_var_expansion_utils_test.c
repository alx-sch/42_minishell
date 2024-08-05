/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion_utils_test.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:58:01 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/05 19:21:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This file contains utility functions for parsing and expanding variables
directly within the passed string, effectively replacing the old 'unexpanded'
string with the 'expanded' one.
*/

#include "minishell.h"

// IN FILE:

int		get_str_l(char **str, int i, char **substr_left);
int		get_str_r(char **str, int i, char *var_name, char **substr_right);
int		join_str_l(char **str, char *str_l, char *var_value);
int		join_str_r(char **str, char *str_r);
void	free_vars(char **var_val, char **str_l, char **str_r);

/**
Extracts a substring from the beginning of the given string up to a
specified index. The extracted substring is stored in `substr_left`.

 @param str 			Pointer to the original string.
 @param i 				Index up to which the substring will be extracted.
 @param substr_left 	Pointer to a char* where the extracted substring will
 						be stored.
 @return	`1` on success,
			`0` on failure (memory allocation failure).
*/
int	get_str_l(char **str, int i, char **substr_left)
{
	*substr_left = malloc(i + 1);
	if (!*substr_left)
		return (0);
	ft_strlcpy(*substr_left, *str, i + 1);
	return (1);
}

/**
 Extracts a substring from a specified index to the end of the string,
 excluding the given variable name. The extracted substring is stored in
 `substr_right`.

 @param str 			Pointer to the original string.
 @param i 				Index from which to start the substring extraction.
 @param var_name 		The variable name to exclude from the substring.
 @param substr_right 	Pointer to a char* where the extracted substring will
					 	be stored.

 @return	`1` on success.
			`0` on failure (memory allocation failure).
*/
int	get_str_r(char **str, int i, char *var_name, char **substr_right)
{
	*substr_right = malloc(ft_strlen(*str) - i - ft_strlen(var_name) + 1);
	if (!*substr_right)
		return (0);
	ft_strlcpy(*substr_right, *str + i + 1 + ft_strlen(var_name),
		strlen(*str) - i - ft_strlen(var_name) + 1);
	return (1);
}

/**
Concatenates `str_l` with `var_value` and replaces `str` with this
concatenation.

 @param str 		Pointer to the existing string which will be replaced by the
 					concatenated result.
 @param str_l 		The first string to concatenate.
 @param var_value 	The second string to concatenate.

 @return	`1` on success (concatenation and memory allocation successful),
			`0` on failure (memory allocation failure).
*/
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

/**
Concatenates `str_r` to the end of `str`.

 @param str 	Pointer to the existing string which will be replaced by the
				concatenated result.
 @param str_r 	The string to concatenate to the end of the existing string.

 @return	`1` on success (concatenation and memory allocation successful),
			`0` on failure (memory allocation failure).
*/
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

/**
Frees dynamically allocated memory for variable values and substrings.
Ensures that only allocated memory is freed and avoids freeing memory
that was not dynamically allocated.

 @param var_val 	Pointer to the dynamically allocated variable value which
 					may need freeing.
 @param str_l 		Pointer to the dynamically allocated substring which may
 					need freeing.
 @param str_r 		Pointer to the dynamically allocated substring which may
 					need freeing.
*/
void	free_vars(char **var_val, char **str_l, char **str_r)
{
	if (ft_strcmp(*var_val, "") == 0) // if var value is empty, it was dynamically allocated -> needs to be freed
		free(*var_val);
	if (*str_l)
		free(*str_l);
	if (*str_r)
		free(*str_r);
}
