/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:59:53 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/13 15:48:18 by nholbroo         ###   ########.fr       */
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

// 1_check_input/check_input.c

int	is_input_empty(char *input);
int	is_quotation_closed(t_data *data);

#endif
