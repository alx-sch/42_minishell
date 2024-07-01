/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:09:18 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/01 20:12:14 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains utility functions used throughout the minishell project.
*/

#include "minishell.h"

// IN FILE:

int	is_whitespace(int c);

/*
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.

Returns:
- 1 if character is a whitespace character.
- 0 otherwise.
*/
int	is_whitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}
