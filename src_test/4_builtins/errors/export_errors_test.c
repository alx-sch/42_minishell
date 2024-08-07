/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errors_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:11:29 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/07 18:24:37 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Called when there is a memory allocation failure in the export command.
Cleans up memory, prints an error message and exits the process.*/
void	export_mem_alloc_failure(t_data *data)
{
	print_err_msg_prefix("export");
	free_data(data, 1);
	exit(ENOMEM); ; // @Busedame: errno specified here, as errno set by failed ft_split is overwritten by some error '2' happening in free_data()
}

static int	print_exp_err_invalid_option(char *input, int i)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	if (input[i + 1])
		{
			write(STDERR_FILENO, &input[i], 1);
			write(STDERR_FILENO, &input[i + 1], 1);
		}
	else
		write(STDERR_FILENO, &input[i], 1);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	return (2);
}

static int	print_exp_err_invalid_identifier(char *input, int i)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd("export: '", STDERR_FILENO);
	while (input[i] && !is_whitespace(input[i]))
			write(STDERR_FILENO, &input[i++], 1);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	errno = EPERM;
	return (errno);
}

/*Two different kinds of error messages for export, one in the case of
invalid option, e.g. "export -b", and the other one in case of invalid
identifier, e.g. "export ds-d"*/
int	export_err_invalid_option(char *input, int i)
{
	if (input[i] == '-')
		return (print_exp_err_invalid_option(input, i));
	return (print_exp_err_invalid_identifier(input, i));
}
