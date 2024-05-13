/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/13 15:44:23 by nholbroo         ###   ########.fr       */
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
		print_error(3); // Prints an error if allocation fails.
	while (i < eol) // We iterate through the current working directory, until we have reached the path to our new directory.
	{
		new_directory[i] = cwd[i]; // Copying over the path to the new directory.
		i++;
	}
	chdir(new_directory); // Changing directory to newly defined directory.
}

static void	cd_to_home_user(char *input, char **envp)
{
	
}

void	cd(char *input, char **envp)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd))) // Get the current working directory.
		print_error(2);
	if (!ft_strcmp(input, "cd")) // If "cd" is the only input, without any arguments.
		cd_to_home_user(input, envp) // Changing directory to /home/user.
	else if (!ft_strcmp(input, "cd ..")) // If "cd .." is the only input.
		cd_one_down(cwd); // Changes the working directory to one level down.
}
