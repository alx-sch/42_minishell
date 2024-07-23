/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:48:26 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 14:27:52 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints an error message if there are too many arguments to cd command.
int	too_many_args_cd(t_cd **cd)
{
	write(2, "cd: too many arguments\n", 24);
	free_cd_struct(cd);
	return (0);
}

// Prints an error message if there is a memory allocation failure for t_cd
// struct.
static void	mem_alloc_fail_cd(t_cd **cd)
{
	free_cd_struct(cd);
	errno = ENOMEM;
	perror("minishell: cd");
	exit(errno);
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
	if (error_code == 1)
		mem_alloc_fail_cd(cd);
	file_name = ft_strrchr((*cd)->subdirectory, '/');
	file_name++;
	error_msg = ft_strjoin("minishell: cd: ", file_name);
	if (!error_msg)
		mem_alloc_fail_cd(cd);
	perror(error_msg);
	free(error_msg);
}
