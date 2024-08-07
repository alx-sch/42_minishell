/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:12:38 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/06 16:55:33 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file declares functions responsible for executing commands
in the minishell after the parsing phase. It includes preparation, piping,
redirections, execution of commands and built-ins and error handling.
*/

#ifndef EXECUTION_H
# define EXECUTION_H

# include "types.h"

// 3_Execution:

void	execution(t_data *data, t_exec *exec, int position);

// 3_Exeuction_prep:

int		init_exec(t_data *data);
int		count_env_list(t_data *data);
void	conv_env_tmp_to_arr(t_data *data, t_exec *exec);
void	move_current_and_update_token(t_list **current, t_token **token);
void	prep_execution(t_data *data, t_exec *exec, int position);
void	get_flags_and_command(t_data *data, t_exec *exec, int position);
int		cmd_is_path(t_data *data, t_exec *exec);
void	get_all_paths(t_data *data, t_exec *exec);
void	get_correct_path(t_data *data, t_exec *exec);

// 3_Execution_piping:

void	create_pipe(t_data *data, t_exec *exec);
void	handle_pipe_in_parent(t_data *data, t_exec *exec);
void	close_pipe_in_parent(t_data *data, t_exec *exec);

// 3_Execution_redirections:

void	check_file_exist_child(t_data *data, t_exec *exec);
void	check_file_exist_parent(t_data *data, t_exec *exec);
void	check_redirections(t_data *data, t_exec *exec, int position);
void	redirections(t_data *data, t_exec *exec);

// 3_Execution_freeing_functions:
void	free_children(t_child *child);
int		free_exec(t_exec *exec);

// 3_Execution_errors:

void	exec_errors(t_data *data, t_exec *exec, int error_code);
void	conversion_errors(t_data *data, t_exec *exec, int i);
void	error_incorrect_path(t_data *data, t_exec *exec);
void	redirections_errors(t_data *data, t_exec *exec, int std, int parent);

#endif
