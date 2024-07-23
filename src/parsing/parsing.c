/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:51:02 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/23 14:30:02 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checking if the input is a builtin command, and checks if the arguments are
// valid.
void	parsing(t_data *data)
{
	if (is_pwd(data->input))
		pwd();
	else if (is_cd(data->input))
		cd(data->input, data->envp_temp);
	else if (is_env(data->input))
		env(data->envp_temp);
	else if (is_exit(data))
	{
		get_next_line(-1);
		exit(exit_with_code(data));
	}
	else if (is_unset(data->input))
	{
		unset(data->input, &data->envp_temp);
		unset(data->input, &data->export_list);
	}
	else if (is_export(data->input))
		export(data);
	else if (is_echo(data->input))
		minishell_echo(data);
}
