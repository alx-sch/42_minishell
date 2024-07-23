/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:48:41 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 14:28:25 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees memory in case of memory allocation failure, and exits process.
@param tmp_error_msg Passing the previous part of the error message (freeing it
if it has been allocated)*/
static void	mem_alloc_fail_exit(char *tmp_error_msg)
{
	if (tmp_error_msg)
		free(tmp_error_msg);
	errno = ENOMEM;
	perror("minishell: exit");
	exit(errno);
}

/*Frees allocated memory of the data struct*/
static void	free_mem_exit(t_data *data)
{
	free_env_struct(&data->envp_temp);
	free_env_struct(&data->export_list);
	free_data(data);
}

/*Prints an error message when the exit command is used, if there is more
than one argument*/
void	exit_check_argc(t_data *data)
{
	char	**arguments;

	arguments = ft_split (data->input, ' ');
	if (!arguments)
		mem_alloc_fail_exit(NULL);
	if (count_array_length(arguments) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		ft_freearray(arguments);
		free_mem_exit(data);
		exit(1);
	}
	ft_freearray(arguments);
}

/*Prints an error message when the exit command is used, if the argument is
not numerical*/
void	print_error_exit(t_data *data)
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
	tmp_error_msg = ft_strjoin("minishell: exit: ", exit_argument);
	if (!tmp_error_msg)
		mem_alloc_fail_exit(NULL);
	full_error_msg = ft_strjoin(tmp_error_msg, ": numeric argument required\n");
	if (!full_error_msg)
		mem_alloc_fail_exit(tmp_error_msg);
	write(2, full_error_msg, ft_strlen(full_error_msg));
	free(tmp_error_msg);
	free(full_error_msg);
	free_mem_exit(data);
	exit(2);
}
