/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:35:04 by natalierh         #+#    #+#             */
/*   Updated: 2024/05/25 11:31:14 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int exit_with_code(char *input)
{
    unsigned int     exit_code;

    while ((*input) && (*input < '0' || *input > '9')
        && *input != '-' && *input != '+')
        input++;
    exit_code = (unsigned int) ft_atoi(input);
    return (exit_code);
}

int is_exit(char *input)
{
    int i;

    i = 0;
    while (is_space(input[i])) // Skipping all whitespaces in the beginning
        i++;
    if (input[i++] != 'e') // Hard-checking for "exit".
        return (0);
    if (input[i++] != 'x')
        return (0);
    if (input[i++] != 'i')
        return (0);
    if (input[i++] != 't')
        return (0);
    while ((input[i]) && (is_space(input[i]) 
        || input[i] == '+' || input[i] == '-' 
        || (input[i] >= '0' && input[i] <= '9'))) // Checking if what comes after "exit" is either numerical, '+', '-' or whitespaces. If it's not, then it's not valid.
        i++;
    if (input[i] != '\0') // If something that comes after 'exit' is not whitespace or a number, returning 0. Will need to print correct error messages.
        return (0);
    return (1);
}
