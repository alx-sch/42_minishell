/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:59:53 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/01 06:23:35 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file declares functions used to validate command-line input for the
minishell. It includes checks to ensure that input is not empty and that all
quotation marks are properly closed. These validations help ensure that the
input is well-formed and can be processed further by the shell.
*/

#ifndef INPUT_CHECK_H
# define INPUT_CHECK_H

# include "types.h"

// 1_check_input/check

int	is_input_empty(char *input);
int	is_quotation_closed(t_data *data);

#endif
