/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/01 10:58:27 by aschenk          ###   ########.fr       */
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
	while (input[i] && is_whitespace(input[i])) // Skipping whitespaces in the beginning
		i++;
	if (input[i] && input[i++] != 'c') // Hard-checking for "cd"
		return (0);
	if (input[i] && input[i++] != 'd')
		return (0);
	if (input[i] && !is_whitespace(input[i])) // Only accepting a space after "cd" -> e.g. "cd /". Would not accept "cdd".
		return (0);
	return (1);
}

// Changes current working directory to parent directory ("cd ..").
// Throws an error if memory allocation fails or something goes wrong with
// changing the directory.
static void	cd_one_up(t_cd **cd, char *cwd)
{
	int		eol; // Stands for "end of line".
	int		i;

	i = 0;
	if (!cwd)
		return ;
	eol = ft_strrchr_index(cwd, '/'); // Locating the end of line of parent directory.
	(*cd)->parentdirectory = malloc(eol + 2); // Allocating memory for the parent directory.
	if (!(*cd)->parentdirectory) // Protecting the malloc @Busedame: Still reachables; if malloc fails, also exits program
		print_error_cd(1, cd); // Prints an error and exits if allocation fails.
	while (i < eol) // We iterate through the whole path to the current working directory, until we have reached the path to the parent directory.
	{
		(*cd)->parentdirectory[i] = cwd[i]; // Copying over the path to the parent directory.
		i++; // Iterating i.
	}
	if (eol == 0) // If eol is 0, it means that the parent directory is root.
		(*cd)->parentdirectory[i++] = '/'; // In that case, I hardset the parent directory to root.
	(*cd)->parentdirectory[i] = '\0'; // Null-terminating the new string containing the path to the parent directory.
	if (chdir((*cd)->parentdirectory) == -1) // Changing directory to parent directory.
		print_err_msg_prefix("cd");
}

// Changes current working directory to "home".
// Iterates through the environment variables to find correct "home"-
// directory.
// Throws an error message if it doesn't exist (it has been removed).
static void	cd_to_home_user(t_cd **cd, t_env *envp_temp)
{
	while (envp_temp) // Going through all of envp, which is showing the environment variables.
	{
		if (!ft_strncmp(envp_temp->e_var, "HOME", 4)) // When I find the "HOME="-line, I break the loop, as I know that I will find the /home/username.
			break ;
		envp_temp = envp_temp->next;
	}
	if (!envp_temp)
	{
		print_err_msg_custom("cd: HOME not set", 1);
		errno = EPERM;
		return ;
	}
	(*cd)->home_user = ft_strdup(envp_temp->value); // I store the "HOME="-line in its own variable. @Busedame: Still reachabels detected when malloc fail!
	if (!(*cd)->home_user) // Protecting the malloc.
		print_error_cd(1, cd); // Prints an error and exits if allocation fails.
	if (chdir((*cd)->home_user) == -1) // Changing the current working directory to "/home/<username>".
		print_err_msg_prefix("cd");
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

	if (chdir((*cd)->component[1]) == 0) // If it is an absolute path, then return.
		return ;
	if (!cwd) // If cwd was actually NULL after getcwd-call.
		return ;
	input = ft_strjoin("/", (*cd)->component[1]); // Add a '/' in front of the input directory, to make it valid.
	if (!input) // Protecting the malloc.
		print_error_cd(1, cd);
	(*cd)->subdirectory = ft_strjoin(cwd, input); // Creating the new path by concatening the input directory to the current one.
	if (!(*cd)->subdirectory) // Protecting the malloc.
	{
		free(input);
		print_error_cd(1, cd);
	}
	if (chdir((*cd)->subdirectory) == -1) // Changing to the new directory.
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
	if (!getcwd(cwd, sizeof(cwd))) // Get the current working directory.
		print_err_msg_prefix("cd");
	if (cd->component[1] == NULL) // If "cd" is the only input, without any components.
		cd_to_home_user(&cd, envp_temp); // Changing directory to /home/user.
	else if (!ft_strcmp(cd->component[1], "~")) // If "cd ~" is the only input.
		cd_to_home_user(&cd, envp_temp); // Changing directory to /home/user.
	else if (is_only_duplicates(cd->component[1], '/')) // If "cd /" is the only input.
	{
		if (chdir("/") == -1) // Changing directory to root.
			print_error_cd(2, &cd);
	}
	else if (!ft_strcmp(cd->component[1], "..")) // If "cd .." is the only input.
		cd_one_up(&cd, cwd); // Changes the working directory to its parent directory.
	else // If "cd" is followed by a path, change to that relative or absolute path.
		cd_one_down(&cd, cwd); // Changes the working directory to a subdirectory or an absolute path.
	return (free_cd_struct(&cd)); // Freeing the struct.
}
