/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:48:26 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/22 18:24:51 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints an error message if there are too many arguments to cd command.
int	too_many_args_cd(t_cd **cd)
{
	write(2, "cd: too many arguments\n", 24);
	free_cd_struct(cd); // Freeing the struct.
	return (0);
}

// Prints an error message if there is a memory allocation failure for t_cd
// struct.
static void	mem_alloc_fail_cd(t_cd **cd)
{
	free_cd_struct(cd); // Freeing the struct.
	errno = ENOMEM; // Setting errno to "Memory allocation failure"
	perror("minishell: cd"); // Prints the error message
	exit(errno); // Exits with correct errno code.
}

// Prints an error message for cd command, like memory allocation failure or
// "No such file or directory"-message. 
// @param error_code Error_code = 1 means memory allocation fail, and 
// error_code = 2 means file/directory doesn't exist or similar.
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
