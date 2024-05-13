/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/13 17:18:17 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_strrchr_index(const char *s, int c)
{
	// This function works exactly as ft_strrchr except for this:
	// The return value is an int instead of a pointer, to get the exact
	// location of the last '/', indicating the directory below the current one.
	char	char_c;
	int		i;

	char_c = (char) c;
	i = ft_strlen(s);
	s += i;
	while (i >= 0)
	{
		if (*s == char_c && (size_t)i != ft_strlen(s)) // Also adding a check to skip the last '/', if any.
			return (i);
		i--;
		s--;
	}
	return (-1);
}

static void	cd_one_down(char *cwd)
{
	char	*new_directory;
	int		eol;
	int		i;

	i = 0;
	eol = ft_strrchr_index(cwd, '/'); // Locating the end of line, meaning where we want the path of the new directory to end.
	new_directory = malloc(eol + 1); // Allocating memory for the new directory.
	if (!new_directory) // Protecting the malloc
		print_error(1); // Prints an error if allocation fails.
	while (i < eol) // We iterate through the current working directory, until we have reached the path to our new directory.
	{
		new_directory[i] = cwd[i]; // Copying over the path to the new directory.
		i++;
	}
	chdir(new_directory); // Changing directory to newly defined directory.
}

static void	cd_to_home_user(char **envp)
{
	char	*username;
	char	*new_path;
	int		i;

	i = 0;
	while (envp[i]) // Going through all of envp, showing the environmental variables.
	{
		if (!ft_strncmp(envp[i], "USER=", 5)) // When I find the "USER="-line, I break the loop, as I know that I will find the username.
			break ;
		i++;
	}
	username = ft_strdup(envp[i]); // I store the username in its own variable.
	if (!username) // Protecting the malloc.
	{
		print_error(1);
		return ;
	}
	username += 5; // I move the username-pointer to skip "USER=" and go directly to the name itself.
	new_path = ft_strjoin("/home/", username); // Setting the new path to include the username.
	if (!new_path) // Protecting the malloc.
	{
		print_error(1);
		return ;
	}
	chdir(new_path); // Changing the current working directory to "/home/<username>".
}

void	cd_one_up(char *input, char *cwd)
{
	char	*new_path;

	input += 3;
	if (chdir(input) == 0)
		return ;
	input = ft_strjoin("/", input);
	if (!input)
	{
		print_error(1);
		return ;
	}
	new_path = ft_strjoin(cwd, input);
	if (!new_path)
	{
		print_error(1);
		return ;
	}
	printf("%s\n", new_path);
	if (chdir(new_path) == -1)
		printf("%s\n", strerror(errno));
}

void	cd(char *input, char **envp)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd))) // Get the current working directory.
		print_error(2);
	if (!ft_strcmp(input, "cd")) // If "cd" is the only input, without any arguments.
		cd_to_home_user(envp); // Changing directory to /home/user.
	else if (!ft_strcmp(input, "cd /")) // If "cd" is the only input, without any arguments.
		chdir("/");
	else if (!ft_strcmp(input, "cd ..")) // If "cd .." is the only input.
		cd_one_down(cwd); // Changes the working directory to one level down.
	else if (ft_strcmp(input, "cd") > 0) // If "cd" is followed by a path, 
		cd_one_up(input, cwd);
	printf ("%s\n", input);
}
