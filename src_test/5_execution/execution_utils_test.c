/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:06:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/06 13:46:35 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Moves current, which is the current node of the list. Updates token
with the content of the node.*/
void	move_current_and_update_token(t_list **current, t_token **token)
{
	*current = (*current)->next;
	if (*current)
		*token = (t_token *)(*current)->content;
}

/*Counts the length (how many nodes) of the env_temp-list. Returns the count.*/
int	count_env_list(t_data *data)
{
	t_env	*current;
	int		count;

	current = data->envp_temp;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*Converts the envp_temp-list to an array - containing the same information,
but with a difference. While the envp_temp-list separates between the
variable name and the value, and also doesn't include the "="-sign, the
strings of the array contain all of it. Like this: "NAME=nholbroo".*/
void	conv_env_tmp_to_arr(t_data *data, t_exec *exec)
{
	int		i;
	t_env	*current;
	char	*tmp;

	i = 0;
	tmp = NULL;
	current = data->envp_temp;
	exec->envp_temp_arr = malloc(sizeof(char *) * (count_env_list(data) + 1));
	if (!exec->envp_temp_arr)
		exec_errors(data, exec, 1);
	while (current)
	{
		tmp = ft_strjoin(current->e_var, "=");
		if (!tmp)
			conversion_errors(data, exec, i);
		exec->envp_temp_arr[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!exec->envp_temp_arr[i])
			conversion_errors(data, exec, i);
		i++;
		current = current->next;
	}
	exec->envp_temp_arr[i] = NULL;
}
