/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:41 by nholbroo          #+#    #+#             */
/*   Updated: 2024/06/24 12:46:47 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
	data->pipe_no = 0;
	data->envp = envp;
	data->envp_temp = NULL;
	data->envp_temp = init_env_tmp(envp);
	data->export_list = NULL;
	data->export_list = init_export_list(data);
	data->input = NULL;
	data->tmp = NULL;
	data->quote = '\0';
	data->tok.tok = NULL;
	data->tok.new_node = NULL;
	data->tok.tok_lst = NULL;
}
