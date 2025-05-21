/**
This file contains a function to check the input string for a pipe symbol ('|')
and creates the corresponding token if the syntax before and after the piping
is valid.

Returns an error message if the piping syntax is not valid.
*/

#include "minishell.h"

// IN FILE:

int	is_pipe(t_data *data, int *i);

/**
Used in check_syntax().
Mostly a simplified version of is_valid_operand() in tokenizer_redirection.c.

Scans the input string starting from the current index (*i).
Skips any leading whitespace and checks if the encountered character is valid.
Valid syntax after a pipe: Anything but '|' and end of input ('\0').

 @param inp 	The input string containing the command line input.
 @param i 		The current index in the input string.

 @return	The dynamically allocated string containing the invalid syntax symbol
  			('newline' for '\0' to mirror the behavior of invalid redirections).
			`NULL` if the syntax is valid or no input before '|'
			(invalid syntax).
			`"ERR"` string literal as fallback, if memory allocation fails while
			attempting to allocate space for the invalid syntax.
*/
static char	*is_valid_syntax(t_data *data, int j)
{
	char	*invalid_syn;

	j += 1;
	invalid_syn = NULL;
	while (is_whitespace(data->input[j]))
		j++;
	if (data->input[j] == '|' || data->input[j] == '&'
		|| data->input[j] == '!' || data->input[j] == '\0')
	{
		invalid_syn = malloc(sizeof(char) * (ft_strlen("newline") + 1));
		if (!invalid_syn)
			return ("ERR");
		if (data->input[j] == '\0')
			ft_strlcpy(invalid_syn, "newline", 8);
		else
		{
			invalid_syn[0] = data->input[j];
			invalid_syn[1] = '\0';
		}
		return (invalid_syn);
	}
	return (NULL);
}

/**
Used in check_syntax().

Prints an error message for invalid syntax encountered after a pipe symbol ('|')
and updates the `errno` accordingly.

 @param invalid_syn The invalid operand encountered in the input.
 @param str_j 		The string representation of int j
 					(position of failed piping).
 @param data 		Pointer to the data structure including the
 					exit status member.
 @param empty 		Flag to indicate if 'empty pipe' msg should be printed
 					(other than zero) or not (`0`).
*/
static void	print_pipe_err_msg(char *invalid_syn, char *str_j, t_data *data,
	int empty)
{
	ft_putstr_fd(ERR_COLOR, STDERR_FILENO);
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	if (empty)
		ft_putstr_fd(ERR_EMPTY_PIPE, STDERR_FILENO);
	else
	{
		ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
		ft_putstr_fd("'|': '", STDERR_FILENO);
		ft_putstr_fd(invalid_syn, STDERR_FILENO);
	}
	ft_putstr_fd("' (position: ", STDERR_FILENO);
	ft_putstr_fd(str_j, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	data->exit_status = ENOENT;
}

// Frees the allocated memory if it was allocated before.
static void	free_syntax_vars(char *invalid_syn, char *str_j)
{
	if (invalid_syn && ft_strcmp(invalid_syn, "ERR") != 0)
		free(invalid_syn);
	if (str_j && ft_strcmp(str_j, "-1") != 0)
		free(str_j);
}

/**
Used in is_pipe().

Checks if the syntax before/after an encountered '|' valid.
If syntax is invalid, it prints a custom error message including the
position of the invalid synatax (position '-1'and 'ERR' syntax error
used as fallback if malloc fails; ERR_MALLOC printend to indicate malloc failure
in these cases).

 @param data 	Data structure containing token-related info.
 @param j 		The index of the piping symbol ('|').

 @returns	`0` if syntax is invalid and an error message was printed
			or malloc fail.
			`1` if the syntax is valid.
*/
static int	check_syntax(t_data *data, int j)
{
	char	*invalid_syn;
	char	*str_j;

	invalid_syn = is_valid_syntax(data, j);
	if (invalid_syn != NULL || data->tok.tok_lst == NULL)
	{
		str_j = ft_itoa(j);
		if (!str_j)
			str_j = "-1";
		if (ft_strcmp(str_j, "-1") == 0)
			print_err_msg(ERR_MALLOC);
		if (data->tok.tok_lst == NULL)
			print_pipe_err_msg(invalid_syn, str_j, data, 1);
		else
		{
			if (ft_strcmp(str_j, "-1") != 0
				&& ft_strcmp(invalid_syn, "ERR") == 0)
				print_err_msg(ERR_MALLOC);
			print_pipe_err_msg(invalid_syn, str_j, data, 0);
		}
		free_syntax_vars(invalid_syn, str_j);
		return (0);
	}
	return (1);
}

/**
If the character at index *i in the input string is a pipe symbol ('|'),
the function checks if the syntax before and after the '|' is valid.
Input before and after a pipe cannot be empty.
Our minishell interprets '||' as "empty input between pipes" not as
"OR" operator.

If the syntax is valid, it creates the corresponding token and adds
it to the token list.

 @param data 	Data structure containing input string and token list.
 @param i 		Pointer to the current index in the input string.

 @return	`1` if a pipe token was added to the token list or if input[*i]
 			is not a pipe.
 			`0` if token creation failed (malloc failure).
			`-1` if the syntax is invalid.
*/
int	is_pipe(t_data *data, int *i)
{
	int	j;

	if (data->input[*i] == '|')
	{
		j = *i;
		if (check_syntax(data, j))
		{
			data->tok.new_node = create_tok(data, PIPE, "|", i);
			if (!data->tok.new_node)
			{
				free_unlinked_token(data);
				return (0);
			}
			ft_lstadd_back(&data->tok.tok_lst, data->tok.new_node);
			return (1);
		}
		else
			return (-1);
	}
	else
		return (1);
}
