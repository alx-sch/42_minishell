#include "minishell.h"

/*Checks for the '/'-sign in the command string, to check if it's
a path.
Returns 1 if it is a path.
Returns 0 if it is NOT a path.*/
int	cmd_is_path(t_data *data, t_exec *exec)
{
	if (ft_strchr(exec->cmd, '/'))
	{
		exec->current_path = ft_strdup(exec->cmd);
		if (!exec->current_path)
			exec_errors(data, exec, 1);
		return (1);
	}
	return (0);
}

/*Uses ft_strjoin to add a "/"-sign at the end of each path, so it can easily
be executed later on.*/
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

/*Iterates through the envp_temp_arr to look for "PATH". If found, it stores
the paths in exec->all_paths.*/
void	get_all_paths(t_data *data, t_exec *exec)
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
			if (!exec->all_paths)
				exec_errors(data, exec, 1);
			add_slash_at_end_of_all_paths(data, exec, tmp);
			free(tmp);
			return ;
		}
		i++;
	}
	exec_errors(data, exec, 2);
}

/*Iterates through all the paths in the environmental variable $PATH,
and checks if that path + the command would be executable. If that's not
the case after iterating through all the paths, it throws an error message
and exits the process.*/
void	get_correct_path(t_data *data, t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->all_paths[i])
	{
		if (exec->current_path)
			free(exec->current_path);
		exec->current_path = ft_strjoin(exec->all_paths[i], exec->cmd);
		if (access(exec->current_path, X_OK) == 0)
			break ;
		i++;
	}
	if (access(exec->current_path, X_OK) != 0)
		error_incorrect_path(data, exec);
}
