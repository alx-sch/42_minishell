/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_prep_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:06:04 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/06 16:29:04 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Different functions to prepare for execution. 
1.Converts the envp_temp linked list to an array. 
2. Checks if there are any redirections, and stores the file indicated to be 
redirected to. 
3. Extracts the command and its flags and stores the command in a string and 
the command + flags in an array.
4. Gets all the paths from the newly created envp_temp-array, if path is not
defined in the command-input.
5. Finds the correct path for the executable.*/
void	prep_execution(t_data *data, t_exec *exec, int position)
{
	conv_env_tmp_to_arr(data, exec);
	check_redirections(data, exec, position);
	get_flags_and_command(data, exec, position);
	redirections(data, exec);
	if (!cmd_is_path(data, exec) && !is_builtin(exec))
	{
		get_all_paths(data, exec);
		get_correct_path(data, exec);
	}
}
