#include "minishell.h"

/*If the command turns out to be a non-builtin command, or a builtin that
can get handled in a child process, the exec struct gets freed and properly
reset. In this way, it goes "freshly" into a child process.*/
void	reset_exec(t_exec *exec)
{
	exec->count_flags = 0;
	exec->cmd_found = 0;
	exec->first = 1;
	if (exec->cmd)
	{
		free(exec->cmd);
		exec->cmd = NULL;
	}
	if (exec->flags)
	{
		ft_freearray(exec->flags);
		exec->flags = NULL;
	}
}

/*Checking for the existence of an infile or outfile, and handles this
the same way as bash. If an infile doesn't exist, it throws out an error
message. If an outfile doesn't exist, the outfile is created.*/
void	check_file_exist_parent(t_data *data, t_exec *exec)
{
	if (exec->redir_in)
	{
		if (access(exec->infile, F_OK) == -1)
			redirections_errors(data, exec, 0, 1);
	}
	if (exec->redir_out)
	{
		if (access(exec->outfile, F_OK == -1))
		{
			exec->outfile_fd = open(exec->outfile, O_CREAT);
			if (exec->outfile_fd == -1)
				redirections_errors(data, exec, 1, 1);
			close(exec->outfile_fd);
			exec->outfile_fd = 0;
		}
	}
}

/*This function gets called if there are no pipes, and only one builtin -
either unset, export with arguments, cd or exit. These builtins need to happen
in the parent process to actually have any effect, as they're modifying the
environment. The function checks for redirections (which are not handled in 
parent, but child, but still makes the check). It executes the builtin, frees 
the allocated memory, and returns.*/
int	execution_only_in_parent(t_data *data, t_exec *exec)
{
	check_redirections(data, exec, 0);
	check_file_exist_parent(data, exec);
	data->exit_status = builtin(data, exec);
	free_exec(exec);
	return (0);
}
