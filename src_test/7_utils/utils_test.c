/*
This file contains utility functions used throughout the minishell project,
such as character classification.
*/

#include "minishell.h"

// IN FILE:

int		is_whitespace(int c);
int		contains_quotes(const char *str);
void	set_path_to_file(t_data *data, char **str, char *file, char *err_msg);
void	minishell_prompt(t_data *data);
void	handle_g_signal(t_data *data);

/**
Checks if a character is a whitespace character:
space, tab, newline, vertical tab, form feed, or carriage return.

 @param c The character to check.

 @return	`1` if the character is one of the whitespace characters.
 			`0` otherwise.
*/
int	is_whitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/**
Checks if a string contains either single or double quotes.

 @param str 	The string to be checked.

 @return		`1` if the string contains at least one single or double quote.
				`0` otherwise.
*/
int	contains_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

/**
Creates a full file path by combining the working directory stored in the `data`
structure with the specified `file` name. It dynamically allocates memory for the
resulting path and assigns it to the `path` pointer. If memory allocation fails,
or if any error occurs, it will print an error message and terminate the program.

 @param data 		Pointer to a t_data structure containing the working directory.
 @param path 		Pointer to a char* where the constructed file path will be stored.
					The function updates this pointer to point to the newly
					allocated path.
 @param file 		The name of the file to be appended to the working directory.
 @param err_msg 	A custom error message to be printed if memory allocation fails.
*/
void	set_path_to_file(t_data *data, char **path, char *file, char *err_msg)
{
	*path = ft_strjoin(data->working_dir, file);
	if (!*path)
	{
		free_data(data, 1);
		print_err_msg(err_msg);
		exit(EXIT_FAILURE);
	}
}

/**
Displays a command prompt to the user and reads their input.

This function uses the `readline` library to show a prompt (specified by
the `PROMPT` macro) and captures the user's input. If the user signals an
intention to exit (e.g., by pressing Ctrl+D), the function calls
`process_exit_signal` to handle the termination gracefully.

 @param data 	A pointer to the data structure. The user's input will be
 				stored in the `input` field of this structure.
*/
void	minishell_prompt(t_data *data)
{
	data->input = readline(PROMPT);
	if (!data->input)
		handle_eot(data);
}

/**
Sets the exit status based on the received signal.
This function handles signals in different contexts: `SIGINT` during prompt
input, heredoc prompt, and execution; `SIGQUIT` during execution (but ignored
during prompt and heredoc prompt).

 @param data 	A pointer to the data structure where the exit status will
 				be updated based on the signal received.
*/
void	handle_g_signal(t_data *data)
{
	if (g_signal == 1)
		data->exit_status = (EKEYREVOKED + SIGINT);
	else if (g_signal == 2)
		data->exit_status = (EKEYREVOKED + SIGQUIT);
	g_signal = 0;
}

// // // Function to print the list of tokens
// // // FOR TESTING ONLY; use `print_token_list(data.tok.tok_lst)` in main().
// void	print_token_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		t_token *token = lst->content;
// 		printf("Position[%d]: '%s' (token type: %d)\n", token->position, token->lexeme, token->type);
// 		lst = lst->next;
// 	}
// }
