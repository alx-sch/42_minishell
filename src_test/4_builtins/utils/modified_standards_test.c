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

/*Checks if all the characters in an array of strings is an alphabetical 
character or a number. Checks each string separately, up until an '='-sign
is found.
Returns 1 if all the data is alphanumerical.
Return 0 if a non-number or non-alphabetical character is found.*/
int	ft_is_alphanumerical(char **flags)
{
	int	i;
	int	str;

	i = 0;
	str = 1;
	while (flags[str])
	{
		while (flags[str][i] && flags[str][i] != '=')
		{
			if ((flags[str][i] < '0' || flags[str][i] > '9') && 
				!is_letter(flags[str][i]))
				return (0);
			i++;
		}
		str++;
	}
	return (1);
}
