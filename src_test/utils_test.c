/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/08 23:08:12 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
Prints an error message to stderr, frees memory allocated within the
fdf structure and exits the program.
*/
void	msg_and_exit(char *msg, t_data *data)
{
	char	*prefixed_msg;

	prefixed_msg = ft_strjoin(ERR_PREFIX, msg);
	if (!prefixed_msg)
		perror_and_exit(ERR_MALLOC, data);
	ft_putstr_fd(prefixed_msg, STDERR_FILENO);
	free(prefixed_msg);
	free_data(data);
	exit(EXIT_FAILURE);
}

/*
Prints an error message to stderr via perror(), which also prints the last
encountered error and frees memory allocated within the fdf structure.
Then, exits the program.
*/
void	perror_and_exit(char *msg, t_data *data)
{
	perror(msg);
	free_data(data);
	exit(EXIT_FAILURE);
}

// FOR TESTING!!
void	print_string_array(char **array)
{
	int	counter;

	counter = 1;
	while (*array != NULL)
	{
		printf("token[%d]: %s\n", counter, *array);
		counter++;
		array++;
	}
}
