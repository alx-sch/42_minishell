/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:05 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/21 17:06:07 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// /*
// Prints an error message to stderr, frees memory allocated within the
// fdf structure and exits the program.
// */
// void	msg_and_exit(char *msg, t_data *data)
// {
// 	char	*prefixed_msg;

// 	prefixed_msg = ft_strjoin(ERR_PREFIX, msg);
// 	if (!prefixed_msg)
// 		perror_and_exit(ERR_MALLOC, data);
// 	ft_putstr_fd(prefixed_msg, STDERR_FILENO);
// 	free(prefixed_msg);
// 	free_data(data);
// 	exit(EXIT_FAILURE);
// }

// /*
// Prints an error message to stderr via perror(), which also prints the last
// encountered error and frees memory allocated within the fdf structure.
// Then, exits the program.
// */
// void	perror_and_exit(char *msg, t_data *data)
// {
// 	perror(msg);
// 	free_data(data);
// 	exit(EXIT_FAILURE);
// }

// // FOR TESTING!!
// void	print_string_array(char **array)
// {
// 	int	counter;

// 	counter = 1;
// 	while (*array != NULL)
// 	{
// 		printf("token[%d]: %s\n", counter, *array);
// 		counter++;
// 		array++;
// 	}
// }

// Prints a custom, color-coded logo for the minishell project.
// void	print_logo(void)
// {
// 	printf("%s%s _  _   ", BOLD, L_RED);
// 	printf("%s__   %s__ _   ", ORANGE, YELLOW);
// 	printf("%s__   %s____   ", GREEN, BLUE);
// 	printf("%s_  _   %s____   ", VIOLET, L_RED);
// 	printf("%s__     %s__   \n", ORANGE, YELLOW);
// 	printf("%s( \\/ ) %s(  ) ", L_RED, ORANGE);
// 	printf("%s(  ( \\ %s(  ) ", YELLOW, GREEN);
// 	printf("%s/ ___) %s/ )( \\ ", BLUE, VIOLET);
// 	printf("%s(  __) %s(  )   ", L_RED, ORANGE);
// 	printf("%s(  )  \n", YELLOW);
// 	printf("%s/ \\/ \\  %s)(  ", L_RED, ORANGE);
// 	printf("%s/    /  %s)(  ", YELLOW, GREEN);
// 	printf("%s\\___ \\ %s) __ (  ", BLUE, VIOLET);
// 	printf("%s) _)  %s/ (_/\\ ", L_RED, ORANGE);
// 	printf("%s/ (_/\\ \n", YELLOW);
// 	printf("%s\\_)(_/ %s(__) ", L_RED, ORANGE);
// 	printf("%s\\_)__) %s(__) ", YELLOW, GREEN);
// 	printf("%s(____/ %s\\_)(_/ ", BLUE, VIOLET);
// 	printf("%s(____) %s\\____/ ", L_RED, ORANGE);
// 	printf("%s\\____/\n\n", YELLOW);
// 	printf("%s%s", RESET, BOLD);
// 	printf("by Natalie Holbrook & Alex Schenk @42 Berlin, July 2024\n\n");
// 	printf("%s", RESET);
// }
