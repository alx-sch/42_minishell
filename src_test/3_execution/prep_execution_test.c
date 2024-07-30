/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:06:04 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/30 14:10:53 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	conv_env_tmp_to_arr(t_data *data, t_exec *exec)
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

static void	add_slash_at_end_of_all_paths(t_data *data, t_exec *exec, char *tmp)
{
	int	i;

	i = 0;
	while (exec->all_paths[i])
	{
		tmp = ft_strjoin(exec->all_paths[i], "/");
		if (!tmp)
			exec_errors(data, exec, 1);
		free(exec->all_paths[i]);
		exec->all_paths[i] = ft_strdup(tmp);
		free(tmp);
		if (!exec->all_paths[i])
			exec_errors(data, exec, 1);
		i++;
	}
}

static void	get_paths(t_data *data, t_exec *exec)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (exec->envp_temp_arr[i])
	{
		if (ft_strncmp(exec->envp_temp_arr[i], "PATH", 4) == 0)
		{
			tmp = ft_substr(exec->envp_temp_arr[i], 5, \
			ft_strlen(exec->envp_temp_arr[i]));
			if (!tmp)
				exec_errors(data, exec, 1);
			exec->all_paths = ft_split(tmp, ':');
			free(tmp);
			if (!exec->all_paths)
				exec_errors(data, exec, 1);
			add_slash_at_end_of_all_paths(data, exec, tmp);
			break ;
		}
		i++;
	}
}

void	prep_execution(t_data *data, t_exec *exec)
{
	conv_env_tmp_to_arr(data, exec);
	get_paths(data, exec);
	printf("%s\n", data->tok.tok->lexeme);
}
