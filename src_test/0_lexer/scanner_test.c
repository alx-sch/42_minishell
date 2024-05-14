/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:59:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/14 17:27:08 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
FOR TESTING ONLY!!
*/
void	print_token(const t_list *current)
{
	t_token	*token;

	token = (t_token *)(current)->content;
	printf("token type :%u, lexeme: %s position %d", token->type, token->lexeme,
		token->position);
	return ;
}

void	print_token_list(t_list *token_list)
{
	t_list	*current;

	current = token_list;
	while (current != NULL)
	{
		print_token(current);
		current = current->next;
	}
	return ;
}

/*
Creates a new token structure and wraps it in a linked list node.
The token contains information about its type, lexeme, and position.
*/
t_list	*create_token(t_token_type type, const char *lexeme, int *i)
{
	t_token	*token; // Declare a pointer to a token structure
	t_list	*new_node; // Declare a pointer to a linked list node

	token = ft_calloc(1, sizeof(t_token)); // Allocate memory for a new token structure
	if (token == NULL)
	{
		perror("malloc token");
		return (NULL);
	}
	// Initialize the token fields
	token->type = type;
	token->lexeme = ft_strdup(lexeme); // Copy the lexeme string
	token->position = *i; // Set the token position
	*i = *i + ft_strlen(lexeme); // Update the position pointer to the end of the lexeme
	ft_printf("token created %p -%s-", token, token->lexeme); // for TESTING ONLY
	new_node = ft_lstnew(token);  // Create a new linked list node with the token as its content
	if (new_node == NULL)
	{
		perror("malloc new_node");
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
// t_list	*create_token_list(const char *input)
// {
// 	printf("Scanning input: %s", input); // FOR TESTING ONLY!
// 	int		i;
// 	char	*tmp;
// 	t_list	**print_token_list;
// 	t_list	*token;

// 	i = 0;
// 	token



// }
