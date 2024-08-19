/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:41 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/19 20:05:47 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN FILE:

void	init_data_struct(t_data *data, int argc, char **argv, char **envp);

/**
This function obtains the current working directory using the `getcwd` function,
and stores it in the `working_dir` member of the data structure.

 @param data 	Pointer to the `data` structure where the current working
 				directory will be stored in the `working_dir` member.
*/
static void	get_cwd(t_data *data)
{
	char	cwd[MAX_BUFFER];
	char	*tmp;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		print_err_msg(ERR_GET_CWD);
		free_data(data, 1);
		exit(EXIT_FAILURE);
	}
	tmp = ft_strdup(cwd);
	data->working_dir = ft_strjoin(tmp, "/");
	if (tmp)
		free(tmp);
	if (!data->working_dir)
	{
		print_err_msg(ERR_GET_CWD);
		free_data(data, 1);
		exit(EXIT_FAILURE);
	}
}

/**
Used in main().

Initializes members of all data structures to starting values.
This helps to prevent accessing uninitialized variables.
*/
void	init_data_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->input = NULL;
	data->pipe_nr = 0;
	data->exit_status = 0;
	data->working_dir = NULL;
	data->path_to_hist_file = NULL;
	data->tok.tok = NULL;
	data->tok.tmp = NULL;
	data->tok.quote = '\0';
	data->tok.new_node = NULL;
	data->tok.tok_lst = NULL;
	data->tok.curr_node = NULL;
	data->tok.curr_tok = NULL;
	data->tok.next_tok = NULL;
	data->envp_temp = NULL;
	data->envp_temp = init_env_tmp(envp);
	data->export_list = NULL;
	data->export_list = init_export_list(data);
	data->quote.in_single = false;
	data->quote.in_double = false;
	get_cwd(data);
	data->path_to_hist_file = init_history(data);
}
