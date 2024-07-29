/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/07/29 19:07:53 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if input is "cd". Ignores whitespaces in the beginning/end.
//
// Returns 0 upon error (e.g. "cdd" instead of "cd").
// Returns 1 upon success.
// NB! SOME WEIRD ERROR HERE IF YOU TYPE ONLY "c".
int	is_cd(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (input[i] && input[i++] != 'c')
		return (0);
	if (input[i] && input[i++] != 'd')
		return (0);
	if (input[i] != '\0' && !is_whitespace(input[i]))
		return (0);
	return (1);
}

// Changes current working directory to parent directory ("cd ..").
// Throws an error if memory allocation fails or something goes wrong with
// changing the directory.
static void	cd_one_up(t_cd **cd, char *cwd)
{
	int		eol;
	int		i;

	i = 0;
	if (!cwd)
		return ;
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
		perror("minishell: cd");
}

// Changes current working directory to "home".
// Iterates through the environment variables to find correct "home"-
// directory.
// Throws an error message if it doesn't exist (it has been removed).
static void	cd_to_home_user(t_cd **cd, t_env *envp_temp)
{
	while (envp_temp)
	{
		if (!ft_strncmp(envp_temp->e_var, "HOME", 4))
			break ;
		envp_temp = envp_temp->next;
	}
	if (!envp_temp)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return ;
	}
	(*cd)->home_user = ft_strdup(envp_temp->value);
	if (!(*cd)->home_user)
		print_error_cd(1, cd);
	if (chdir((*cd)->home_user) == -1)
		perror("minishell: cd");
}

// Moves to a subdirectory or an absolute path.
// First checks if it is a valid absolute path ("cd /home/natalierh"). In that
// case it changes current working directory to that.
// Otherwise moves on to change to a defined subdirectory.
//
// Throws an error if the defined subdirectory doesn't exist.
void	cd_one_down(t_cd **cd, char *cwd)
{
	char	*input;

	if (chdir((*cd)->component[1]) == 0)
		return ;
	if (!cwd)
		return ;
	input = ft_strjoin("/", (*cd)->component[1]);
	if (!input)
		print_error_cd(1, cd);
	(*cd)->subdirectory = ft_strjoin(cwd, input);
	if (!(*cd)->subdirectory)
	{
		free(input);
		print_error_cd(1, cd);
	}
	if (chdir((*cd)->subdirectory) == -1)
		print_error_cd(2, cd);
	free(input);
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
int	cd(char *input, t_env *envp_temp)
{
	char		cwd[4096];
	t_cd		*cd;

	cd = NULL;
	init_cd_struct(&cd, input);
	if (count_array_length(cd->component) > 2)
		return (too_many_args_cd(&cd));
	if (!getcwd(cwd, sizeof(cwd)))
		perror("minishell: cd");
	if (cd->component[1] == NULL)
		cd_to_home_user(&cd, envp_temp);
	else if (!ft_strcmp(cd->component[1], "~"))
		cd_to_home_user(&cd, envp_temp);
	else if (is_only_duplicates(cd->component[1], '/'))
	{
		if (chdir("/") == -1)
			print_error_cd(2, &cd);
	}
	else if (!ft_strcmp(cd->component[1], ".."))
		cd_one_up(&cd, cwd);
	else
		cd_one_down(&cd, cwd);
	return (free_cd_struct(&cd));
}
