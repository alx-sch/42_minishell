/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:13:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/05 14:48:08 by aschenk          ###   ########.fr       */
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
	int	return_process_heredocs;

	return_process_heredocs = process_heredocs(data);
	if (return_process_heredocs <= 0)
	{
		if (return_process_heredocs == 0) // return is '-1' if CTRL+C during heredoc prompt, don't print ERR MESSAGE then
			print_err_msg(ERR_PARSE_HEREDOC);
		return (0);
	}
	if (!expand_variables(&data->input, data))
	{
		print_err_msg(ERR_VAR_EXP);
		return (0);
	}
	return (1);
}
