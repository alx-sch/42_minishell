/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_variable_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:26:07 by aschenk           #+#    #+#             */
/*   Updated: 2024/06/04 17:05:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains a function to check the input string for environmental
variables as well as the special case "$?" (exit status of the last command
executed) and creates the corresponding tokens, if applicable.

It does not create 'quotation' tokens and looks up variables if '$' is not
followed by a variable name or if it is followed by a 'special use' character,
such as $#, $@, $*, etc., which are not handled within minishell.
*/

#include "minishell.h"

// FUNCTION IN FILE

int	is_variable(t_data *data, int *i)
{
	int	j;

	j = *i; // Store the initial index value
	if (data->input[*i] == '$')
	{
		if (data->input[i + 1] == '?')	// Check if '$?' (exit code)
			ft_lstadd_back(&data->tok.tok_lst, create_tok(data, EXIT_CODE, "$?", &i));
		else if (data->input[i + 1] == '?')

	} && data->input[*i + 1] == '>')
		create_redirection_token(data, i, APPEND_OUT, ">>");

		else if (d->input[i] == '$' && d->input[i + 1] == '?') // checks if the shell variable '$?' (exit status) is input
			ft_lstadd_back(&d->tok.tok_lst, create_tok(d, DOLLAR_QUEST, "$?", &i));
