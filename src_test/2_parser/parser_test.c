/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:13:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/29 20:02:05 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#include "minishell.h"

// FUNCTION IN FILE

int	parse_tokens(t_data *data);

int	parse_tokens(t_data *data)
{
	if (!process_heredocs(data))
	{
		print_err_msg(ERR_PARSE_HEREDOC);
		return (0);
	}
	if (!expand_variables(&data->input, data->envp_temp))
	{
		print_err_msg(ERR_VAR_EXP);
		return (0);
	}
	return (1);
}
