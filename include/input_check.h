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

int	is_empty(char *input);
int	is_only_whitespace(char *input);
int	is_quotation_closed(t_data *data);

#endif
