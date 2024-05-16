/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:51:10 by nholbroo          #+#    #+#             */
/*   Updated: 2024/05/16 12:41:42 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cd_one_up(t_cd **cd, char *cwd)
{
	int		eol;
	int		i;

	i = 0;
	eol = ft_strrchr_index(cwd, '/');
	(*cd)->parentdirectory = malloc(eol + 1);
	if (!(*cd)->parentdirectory)
		print_error_cd(1, cd);
	while (i < eol)
	{
		(*cd)->parentdirectory[i] = cwd[i];
		i++;
	}
	(*cd)->parentdirectory[i] = '\0';
	chdir((*cd)->parentdirectory);
}

static void	cd_to_home_user(t_cd **cd, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "USER=", 5))
			break ;
		i++;
	}
	(*cd)->username = ft_strdup(envp[i]);
	if (!(*cd)->username)
		print_error_cd(1, cd);
	(*cd)->username += 5;
	(*cd)->home_user = ft_strjoin("/home/", (*cd)->username);
	if (!(*cd)->home_user)
		print_error_cd(1, cd);
	chdir((*cd)->home_user);
}

void	cd_one_down(t_cd **cd, char *cwd)
{
	char	*input;

	if (chdir((*cd)->component[1]) == 0)
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
	if (!getcwd(cwd, sizeof(cwd)))
		print_error_cd(2, NULL);
	if (cd->component[1] == NULL)
		cd_to_home_user(&cd, envp);
	else if (!ft_strcmp(cd->component[1], "~"))
		cd_to_home_user(&cd, envp);
	else if (is_only_duplicates(cd->component[1], '/'))
		chdir("/");
	else if (!ft_strcmp(cd->component[1], ".."))
		cd_one_up(&cd, cwd);
	else if (ft_strlen(cd->component[1]) > 2)
		cd_one_down(&cd, cwd);
	free_cd_struct(&cd);
}
