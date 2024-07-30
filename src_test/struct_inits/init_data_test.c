/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:41 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 13:03:04 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
Used in main().

Initializes members in the data structure to starting values.
This helps to prevent accessing uninitialized variables, particularly
in functions like free_data(), which is automatically called in case
of program termination due to an error.
*/
void	init_data_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->input = NULL;
	data->pipe_nr = 0;
	data->exit_status = 0;
	data->envp_temp = NULL;
	data->envp_temp = init_env_tmp(envp);
	data->export_list = NULL;
	data->export_list = init_export_list(data);
	data->tok.tmp = NULL;
	data->tok.quote = '\0';
	data->tok.tok = NULL;
	data->tok.new_node = NULL;
	data->tok.tok_lst = NULL;
}
