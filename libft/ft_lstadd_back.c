#include "libft.h"

// Adds the node ’new’ at the end of the list.
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

/*
#include <stdio.h>

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%p", (void *)lst);
		printf("-> %s\n", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list *node1 = ft_lstnew("One");
	t_list *node2 = ft_lstnew("Two");
	t_list *node3 = ft_lstnew("Three");

	node1->next = node2;
	node2->next = node3;

	printf("Linked List before adding a new node: \n");
	print_list(node1);
	printf("\n");

	// Add a new node to the end of the list
	t_list *node4 = ft_lstnew("Four");
	ft_lstadd_back(&node1, node4);

	printf("Linked List after adding a new node: \n");
	print_list(node1);

	// Free the list
	while (node1)
	{
		t_list *temp = node1;
		node1 = node1->next;
		free(temp);
	}

	return (0);
}
*/
