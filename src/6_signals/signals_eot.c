/**
This file contains the handling of the CTRL+D input event (EOT char).

CTRL+D does not generate a traditional signal but sends an End-Of-Transmission
(EOT) character (ASCII value 4) to the standard input. When the EOT character
is encountered, functions like `readline()` interpret this as the end of input
and will return NULL.
*/

#include "minishell.h"

// IN FILE:

void	handle_eot(t_data *data);
void	handle_eot_heredoc(char *delim);

/**
Handles cleanup and program termination in response to the CTRL + D exit signal.

 @param data 	A pointer to a data structure, which will be cleaned up.
 @param str 	A pointer to a dynamically allocated string or buffer to be
 				freed. This parameter can be `NULL` if there is no allocated
				memory to free.
*/
void	handle_eot(t_data *data)
{
	printf("exit\n");
	cleanup(data, 1);
	exit(0);
}

/**
Handles the EOT signal (CTRL + D) during the heredoc prompt.
The EOT signal closes the heredoc in lieu of the expected delimiter, and a
warning message is printed to inform the user.

 @param data 	A pointer to a data structure, which will be cleaned up.
 @param delim	The trimmed delimiter of the heredoc.
*/
void	handle_eot_heredoc(char *delim)
{
	print_err_msg_custom(WARN_EOT_HERE_1, 1, 0);
	print_err_msg_custom(WARN_EOT_HERE_2, 0, 0);
	print_err_msg_custom(delim, 0, 0);
	print_err_msg_custom(WARN_EOT_HERE_3, 0, 0);
	ft_putstr_fd("\n", STDERR_FILENO);
}
