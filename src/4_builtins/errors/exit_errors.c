/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:48:41 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/13 18:53:32 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees memory in case of memory allocation failure, and exits process.
@param tmp_error_msg Passing the previous part of the error message (freeing it
if it has been allocated)*/
static void	mem_alloc_fail_exit(t_data *data, char *tmp_error_msg)
{
	(void)data;
	if (tmp_error_msg)
		free(tmp_error_msg);
	print_err_msg_prefix("exit");
	free_data(data, 1);
	exit(ENOMEM);
}

/*Prints an error message when the exit command is used, if there is more
than one argument*/
void	exit_check_argc(t_data *data)
{
	char	**arguments;

	arguments = ft_split(data->input, ' ');
	if (!arguments)
		mem_alloc_fail_exit(data, NULL);
	if (count_array_length(arguments) > 2)
	{
		print_err_msg_custom("exit: too many arguments", 1);
		ft_freearray(arguments);
		free_data(data, 1);
		exit(EPERM);
	}
	ft_freearray(arguments);
}

/*Prints an error message when the exit command is used, if the argument is
not numerical*/
void	print_error_exit(t_data *data, t_exec *exec)
{
	char	*tmp_error_msg;
	char	*full_error_msg;
	char	*exit_argument;

	tmp_error_msg = NULL;
	full_error_msg = NULL;
	exit_argument = NULL;
	printf("exit\n");
	exit_argument = ft_strchr(data->input, ' ');
	exit_argument++;
	tmp_error_msg = ft_strjoin("exit: ", exit_argument);
	if (!tmp_error_msg)
		mem_alloc_fail_exit(data, NULL);
	full_error_msg = ft_strjoin(tmp_error_msg, ": numeric argument required\n");
	if (!full_error_msg)
		mem_alloc_fail_exit(data, tmp_error_msg);
	print_err_msg_custom(full_error_msg, 0);
	free(tmp_error_msg);
	free(full_error_msg);
	free_exec(exec);
	free_data(data, 1);
	exit(ENOENT);
}
