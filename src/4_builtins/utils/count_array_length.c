#include "minishell.h"

/* Counts the length of an array of strings, meaning how many strings. */
int	count_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
