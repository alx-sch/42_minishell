#include "minishell.h"

/*Prints out the current working directory. If something goes wrong, it prints
an error message with errno set to indicate the error.
@param cwd "Current working directory"*/
int	pwd(t_exec *exec)
{
	char	cwd[4096];

	if (exec->flags[1])
	{
		if (exec->flags[1][0] == '-')
			return (pwd_invalid_option(exec->flags[1], 0));
	}
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		print_err_msg_prefix("pwd");
	return (0);
}
