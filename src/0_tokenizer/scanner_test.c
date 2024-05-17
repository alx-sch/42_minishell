/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:59:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/17 13:03:58 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
t_list -> libft
Creates a new token structure and wraps it in a linked list node.
The token contains information about its type, lexeme, and position.
 - type:	XX
 - lexeme:	XX
 - i:		XXX
*/
t_list	*create_token(t_token_type type, const char *lexeme, int *i)
{
	t_token	*token; // Declare a pointer to the token structure
	t_list	*new_node; // Declare a pointer to a linked list node

	token = ft_calloc(1, sizeof(t_token)); // Allocate memory for the new token structure
	if (token == NULL)
	{
		perror("malloc token"); // probably: substitute with "clean everything and then perror" fct
		return (NULL);
	}
	// Initialize the token fields
	token->type = type; // this is an int, no need to free
	token->lexeme = ft_strdup(lexeme); // CAN FAIL -> CHECK! Copy the lexeme string, eventually needs to be freed
	token->position = *i; // Set the token position
	*i = *i + ft_strlen(lexeme); // Update the position pointer to the end of the lexeme
	ft_printf("Lexem [%d]: '%s' (%d)\n",  token->position, token->lexeme, token->type); // for TESTING ONLY
	new_node = ft_lstnew(token); // Create a new linked list node with the token as its content
	if (new_node == NULL)
	{
		perror("malloc new_node"); // probably: substitute with "clean everything and then exit" fct, then free's not needed below
		free(token->lexeme);
		free(token);
		return (NULL);
	}
	return (new_node); // Return a pointer to the newly created linked list node
}

/*
Returns a token list which is a linked list of t_list type
note: we dont need to action some of them but fir completeness I added
as much as I could. for instance we do not action the last & on a command
or redirections like
*/
t_list	*get_tokens(const char *input)
{
	int		i;
	char	*tmp;
	t_list	*token_list;
	//t_list	*token;
	//char	*name;
	int		start;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		if (is_space(input[i])) // skips whitespace
			i++;
		if (!is_redirection(&token_list, input, &i))
		{
			printf("I am stopping here!\n");
			ft_lstclear(&token_list, del_token);
			return (NULL);
		}
		if (input[i] == '$' && input[i + 1] == '?') // checks if the shell variable '$?' (exit status) is input
			ft_lstadd_back(&token_list, create_token(DOLLAR_QUEST, "$?", &i));
		else // all the rest is considered a COMMAND --> which is not true, could also be a pathfile -> '/' --> bash: /: Is a directory
		{
			start = i;
			while (!is_delimiter(input[i]))
				i++;
			tmp = ft_substr(input, start, i - start);
			ft_lstadd_back(&token_list, create_token(CMD, tmp, &start));
			free(tmp);
		}
	}
	return (token_list);
}
