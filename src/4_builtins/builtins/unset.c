#include "minishell.h"

/*Removes a node from the t_env list.
@param e_var "Environmental variable"
@param value "Value of the environmental variable"
@param current "The current node"*/
static void	unset_remove_variable(t_env **current, t_env **envp_temp, char *arg)
{
	while (*current)
	{
		if (ft_strncmp(arg, (*current)->e_var, ft_strlen(arg)) == 0)
		{
			if ((*current)->next)
				(*current)->next->previous = (*current)->previous;
			if ((*current)->previous)
				(*current)->previous->next = (*current)->next;
			else
				*envp_temp = (*current)->next;
			free((*current)->value);
			free((*current)->e_var);
			free(*current);
			break ;
		}
		*current = (*current)->next;
	}
}

/*Removes one or more environmental variable(s) from the env-list or
export-list. The function is called twice in the file parsing.c, making sure
both lists are updated. If no variables are specified or the variable doesn't
exist, nothing happens.*/
int	unset(t_exec *exec, t_env **envp_temp)
{
	t_env	*current;
	int		i;

	current = *envp_temp;
	i = 1;
	while (exec->flags[i])
	{
		current = *envp_temp;
		unset_remove_variable(&current, envp_temp, exec->flags[i]);
		i++;
	}
	return (0);
}
