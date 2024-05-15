/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_standards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:16:54 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/15 13:27:03 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This first function works exactly as ft_strrchr except for this:
// The return value is an int instead of a pointer.

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
