/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_history_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:14:07 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/08 16:38:09 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	history_errors(char *str, int error_code, int fd)
{
	if (error_code == 1)
	{
		ft_putstr_fd(ERR_PREFIX, 2);
		ft_putstr_fd("'.minishell_history'", 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	if (errno == ENOMEM)
	{
		free(str);
		ft_putstr_fd(ERR_PREFIX, 2);
		perror("");
		close(fd);
		exit(errno);
	}
}

void	add_history_to_file(char *input)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	if (access(".minishell_history", F_OK) == -1)
		fd = open(".minishell_history", O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(".minishell_history", O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		history_errors(NULL, 1, fd);
	while (input[i])
		write(fd, &input[i++], 1);
	write(fd, "\n", 1);
	close(fd);
	add_history(input);
}

void	init_add_history_from_file(char *tmp, char *input, int fd)
{
	while (1)
	{
		free(input);
		free(tmp); 
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		input = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		if (!input)
			history_errors(tmp, 2, fd);
		add_history(input);
	}
}

void	init_history(void)
{
	int		fd;
	char	*input;
	char	*tmp;

	fd = 0;
	if (access(".minishell_history", F_OK) == -1)
		fd = open(".minishell_history", O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (fd == 0)
		fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
		history_errors(NULL, 1, 0);
	tmp = get_next_line(fd);
	if (!tmp)
		history_errors(NULL, 2, fd);
	input = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	if (!input)
		history_errors(tmp, 2, fd);
	if (input)
		add_history(input);
	init_add_history_from_file(tmp, input, fd);
	close(fd);
}
