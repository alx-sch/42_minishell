/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_standards_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:16:54 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 23:51:55 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterates through a string, from start to end, to search for a character.
// It returns its index if it is found. If it's not found, the
// function returns -1.
int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// Iterates through a string, from end to start, to search for a character.
// It returns its index if it is found. If it's not found, the
// function returns -1.
int	ft_strrchr_index(const char *s, int c)
{
	char	char_c;
	int		i;

	char_c = (char) c;
	i = ft_strlen(s);
	s += i;
	while (i >= 0)
	{
		if (*s == char_c)
			return (i);
		i--;
		s--;
	}
	return (-1);
}

/*Checks if the passed string ONLY contains a certain character*/
bool	is_only_duplicates(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			return (false);
		i++;
	}
	return (true);
}

/*Checks if the char is an alphabetical character.*/
int	is_letter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}