/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/19 15:31:31 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Changes current working directory to parent directory ("cd ..").
// Throws an error if memory allocation fails or something goes wrong with
// changing the directory.
// @param eol "End of line"
static int	cd_one_up(t_cd **cd, char *cwd)
{
	int		eol;
	int		i;

	i = 0;
	if (!cwd)
		return (1);
	eol = ft_strrchr_index(cwd, '/');
	(*cd)->parentdirectory = malloc(eol + 2);
	if (!(*cd)->parentdirectory)
		print_error_cd(1, cd);
	while (i < eol)
	{
		(*cd)->parentdirectory[i] = cwd[i];
		i++;
	}
	if (eol == 0)
		(*cd)->parentdirectory[i++] = '/';
	(*cd)->parentdirectory[i] = '\0';
	if (chdir((*cd)->parentdirectory) == -1)
		print_err_msg_prefix("cd");
	return (0);
}

// Changes current working directory to "home".
// Iterates through the environment variables to find correct "home"-
// directory.
// Still works even though HOME is removed with unset.
static int	cd_to_home_user_tilde(t_cd **cd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME", 4))
			break ;
		i++;
	}
	if (!envp[i])
	{
		print_err_msg_custom("cd: HOME not set", 1, 1);
		errno = EPERM;
		return (errno);
	}
	(*cd)->home_user = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!(*cd)->home_user)
		print_error_cd(1, cd);
	if (chdir((*cd)->home_user) == -1)
		print_err_msg_prefix("cd");
	return (0);
}

// Changes current working directory to "home".
// Iterates through the environment variables to find correct "home"-
// directory.
// Throws an error message if it doesn't exist (it has been removed).
static int	cd_to_home_user(t_cd **cd, t_env *envp_temp)
{
	while (envp_temp)
	{
		if (!ft_strncmp(envp_temp->e_var, "HOME", 4))
			break ;
		envp_temp = envp_temp->next;
	}
	if (!envp_temp)
	{
		print_err_msg_custom("cd: HOME not set", 1, 1);
		errno = EPERM;
		return (errno);
	}
	(*cd)->home_user = ft_strdup(envp_temp->value);
	if (!(*cd)->home_user)
		print_error_cd(1, cd);
	if (chdir((*cd)->home_user) == -1)
		print_err_msg_prefix("cd");
	return (0);
}

// Moves to a subdirectory or an absolute path.
// First checks if it is a valid absolute path ("cd /home/natalierh"). In that
// case it changes current working directory to that.
// Otherwise moves on to change to a defined subdirectory.
//
// Throws an error if the defined subdirectory doesn't exist.
static int	cd_one_down(t_cd **cd, char *cwd, t_exec *exec)
{
	char	*input;

	if (chdir(exec->flags[1]) == 0)
		return (0);
	if (!cwd)
		return (1);
	input = ft_strjoin("/", exec->flags[1]);
	if (!input)
		print_error_cd(1, cd);
	(*cd)->subdirectory = ft_strjoin(cwd, input);
	free(input);
	if (!(*cd)->subdirectory)
		print_error_cd(1, cd);
	if (chdir((*cd)->subdirectory) == -1)
		return (print_error_cd(2, cd));
	return (0);
}

// Works like the "cd"-command in bash.
//
// Does not accept:
// -More than one argument.
// -Non-existing file or directory.
//
// Does accept:
// -Whitespaces in the beginning/end.
// -Both relative and absolute paths ("cd .." or "cd /home/nholbroo").
// -Go to home ("cd" or "cd ~").
// -Go to root ("cd /" or even "cd ///////////").
// -Go to subdirectory (type "cd" followed by a subdirectory or press tab-key
// to see a list of different available subdirectories.)
int	cd(t_data *data, t_exec *exec)
{
	char		cwd[4096];
	t_cd		*cd;
	int			exit_status;

	cd = NULL;
	exit_status = 0;
	init_cd_struct(&cd);
	if (count_array_length(exec->flags) > 2)
		return (too_many_args_cd(&cd));
	if (!getcwd(cwd, sizeof(cwd)))
		print_err_msg_prefix("cd");
	if (exec->flags[1] == NULL)
		exit_status = cd_to_home_user(&cd, data->envp_temp);
	else if (!ft_strcmp(exec->flags[1], "~"))
		exit_status = cd_to_home_user_tilde(&cd, data->envp);
	else if (is_only_duplicates(exec->flags[1], '/'))
	{
		if (chdir("/") == -1)
			exit_status = print_error_cd(2, &cd);
	}
	else if (!ft_strcmp(exec->flags[1], ".."))
		exit_status = cd_one_up(&cd, cwd);
	else
		exit_status = cd_one_down(&cd, cwd, exec);
	return (free_cd_struct(&cd, exit_status));
}
