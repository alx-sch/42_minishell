/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:48:41 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 11:49:29 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mem_alloc_fail_exit(char *tmp_error_msg)
{
	if (tmp_error_msg)
		free(tmp_error_msg);
	errno = ENOMEM;
	perror("minishell: exit");
	exit(errno);
}

void	exit_check_argc(char *input)
{
	char	**arguments;

	arguments = ft_split (input, ' ');
	if (!arguments)
		mem_alloc_fail_exit(NULL);
	if (count_array_length(arguments) > 2)
	{
		printf("exit\n");
		write(2, "minishell: exit: too many arguments\n", 36);
		ft_freearray(arguments);
		exit(1);
	}
	ft_freearray(arguments);
}

void	print_error_exit(char *input)
{
	char	*tmp_error_msg;
	char	*full_error_msg;
	char	*exit_argument;

	tmp_error_msg = NULL;
	full_error_msg = NULL;
	exit_argument = NULL;
	printf("exit\n");
	exit_argument = ft_strchr(input, ' '); // Searches for the last occurence of ' ', indicating the location of the filename in the subdirectory-path. I didn't add an error check here since it will always be true.
	exit_argument++; // Incrementing by 1 to skip the '/' character.
	tmp_error_msg = ft_strjoin("minishell: exit: ", exit_argument); // Creating the error message to be the same as in bash.
	if (!tmp_error_msg) // Protecting the malloc.
		mem_alloc_fail_exit(NULL); // In the case of a malloc error the process terminates.
	full_error_msg = ft_strjoin(tmp_error_msg, ": numeric argument required\n");
	if (!full_error_msg)
		mem_alloc_fail_exit(tmp_error_msg);
	write(2, full_error_msg, ft_strlen(full_error_msg));
	free(tmp_error_msg);
	free(full_error_msg); // Frees the error_msg - string.
	exit(2);
}