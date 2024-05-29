/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/29 11:20:45 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will print an error. Either related to memory allocation,
// or in the case where the path doesnt exist. Like "cd sadsad".

static void	mem_alloc_fail_cd(t_cd **cd)
{
	free_cd_struct(cd); // Freeing the struct.
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: cd"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

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

void	print_error_cd(int error_code, t_cd **cd)
{
	char	*error_msg;
	char	*file_name;

	error_msg = NULL; 
	file_name = NULL;
	if (error_code == 1) // Memory allocation failure
		mem_alloc_fail_cd(cd);
	file_name = ft_strrchr((*cd)->subdirectory, '/'); // Searches for the last occurence of '/', indicating the location of the filename in the subdirectory-path. I didn't add an error check here since it will always be true.
	file_name++; // Incrementing by 1 to skip the '/' character.
	error_msg = ft_strjoin("minishell: cd: ", file_name); // Creating the error message to be the same as in bash.
	if (!error_msg) // Protecting the malloc.
		mem_alloc_fail_cd(cd); // In the case of a malloc error the process terminates.
	perror(error_msg); // Prints the error message.
	free(error_msg); // Frees the error_msg - string.
}
