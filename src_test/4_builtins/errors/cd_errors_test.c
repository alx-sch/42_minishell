/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:48:26 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/31 22:01:53 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints an error message if there are too many arguments to cd command.
int	too_many_args_cd(t_cd **cd)
{
	print_err_msg_custom("cd: too many arguments");
	free_cd_struct(cd); // Freeing the struct.
	errno = EPERM;
	return (0);
}

// Prints an error message if there is a memory allocation failure for t_cd
// struct.
static void	mem_alloc_fail_cd(t_cd **cd)
{
	free_cd_struct(cd); // Freeing the struct.
	print_err_msg_prefix("cd");
	exit(errno); // Exits with correct errno code. @Busedame: WHY EXIT AT ALL?
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
	if (!error_msg) // Protecting the malloc. @Busedame: Still reachables if malloc fails
		mem_alloc_fail_cd(cd); // In the case of a malloc error the process terminates.
	print_err_msg(error_msg);
	free(error_msg); // Frees the error_msg - string.
}
