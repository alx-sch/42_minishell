/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:35:04 by natalierh         #+#    #+#             */
/*   Updated: 2024/05/29 11:24:58 by natalierh        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int exit_with_code(char *input)
{
    unsigned int     exit_code;

    while ((*input) && (*input < '0' || *input > '9') // This loop is skipping the input string until the exit number is getting defined. E.g. "exit     -123".
        && *input != '-' && *input != '+')
        input++;
    exit_code = (unsigned int) ft_atoi(input); // Converting the numeral part of the string to an unsigned int.
    return (exit_code); // Returning the exit code.
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
    if (input[i] && !is_space(input[i]))
        return (0);
    while ((input[i]) && (is_space(input[i]) 
        || input[i] == '+' || input[i] == '-' 
        || (input[i] >= '0' && input[i] <= '9'))) // Checking if what comes after "exit" is either numerical, '+', '-' or whitespaces. If it's not, then it's not valid.
        i++;
    exit_check_argc(input); // Checking if there are more than one argument to the "exit" command -> in that case it prints an error message and exits.
    if (input[i] != '\0') // If something that comes after 'exit' is not whitespace or a number, printing an error message, and exiting the process.
        print_error_exit(input);
    return (1);
}
