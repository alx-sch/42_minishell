/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/17 16:31:05 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_one_up(t_cd **cd, char *cwd)
{
	int		eol; // Stands for "end of line".
	int		i;

	i = 0;
	eol = ft_strrchr_index(cwd, '/'); // Locating the end of line of parent directory.
	(*cd)->parentdirectory = malloc(eol + 1); // Allocating memory for the parent directory.
	if (!(*cd)->parentdirectory) // Protecting the malloc
		print_error_cd(1, cd); // Prints an error and exits if allocation fails.
	while (i < eol) // We iterate through the whole path to the current working directory, until we have reached the path to the parent directory.
	{
		(*cd)->parentdirectory[i] = cwd[i]; // Copying over the path to the parent directory.
		i++; // Iterating i.
	}
	(*cd)->parentdirectory[i] = '\0'; // Null-terminating the new string containing the path to the parent directory.
	chdir((*cd)->parentdirectory); // Changing directory to parent directory.
}

static void	cd_to_home_user(t_cd **cd, char **envp)
{
	int		i;

	i = 0;
	while (envp[i]) // Going through all of envp, which is showing the environmental variables.
	{
		if (!ft_strncmp(envp[i], "USER=", 5)) // When I find the "USER="-line, I break the loop, as I know that I will find the username.
			break ;
		i++;
	}
	(*cd)->username = ft_strdup(envp[i]); // I store the username in its own variable.
	if (!(*cd)->username) // Protecting the malloc.
		print_error_cd(1, cd); // Prints an error and exits if allocation fails.
	(*cd)->username += 5; // I move the username-pointer to skip "USER=" and go directly to the name itself.
	(*cd)->home_user = ft_strjoin("/home/", (*cd)->username); // Setting the new path to include the username.
	if (!(*cd)->home_user) // Protecting the malloc.
		print_error_cd(1, cd); // Prints an error and exits if allocation fails.
	chdir((*cd)->home_user); // Changing the current working directory to "/home/<username>".
}

void	cd_one_down(t_cd **cd, char *cwd)
{
	char	*input;

	if (chdir((*cd)->component[1]) == 0) // If it is an absolute path, then return.
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
		printf("%s\n", strerror(errno));
	free(input);
}

void	cd(char *input, char **envp)
{
	char		cwd[4096];
	t_cd		*cd;

	cd = NULL;
	init_cd_struct(&cd, input);
	if (count_array_length(cd->component) > 2)
	{
		print_error_cd(3, &cd);
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd))) // Get the current working directory.
		print_error_cd(2, NULL); // Print an error message.
	if (cd->component[1] == NULL) // If "cd" is the only input, without any components.
		cd_to_home_user(&cd, envp); // Changing directory to /home/user.
	else if (!ft_strcmp(cd->component[1], "~")) // If "cd ~" is the only input.
		cd_to_home_user(&cd, envp); // Changing directory to /home/user.
	else if (is_only_duplicates(cd->component[1], '/')) // If "cd /" is the only input.
		chdir("/"); // Changing directory to root.
	else if (!ft_strcmp(cd->component[1], "..")) // If "cd .." is the only input.
		cd_one_up(&cd, cwd); // Changes the working directory to its parent directory.
	else if (ft_strlen(cd->component[1]) > 2) // If "cd" is followed by a path, change to that relative or absolute path.
		cd_one_down(&cd, cwd); // Changes the working directory to a subdirectory.
	free_cd_struct(&cd); // Freeing the struct.
}

// If there are too many arguments, print an error message.
// Implement something to handle several '///////'!!
