/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:19:19 by noudrib           #+#    #+#             */
/*   Updated: 2024/04/09 17:16:26 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL)
	{
		new -> next = NULL;
		*lst = new;
	}
	else
	{
		new -> next = *lst;
		*lst = new;
	}
}

/*void	print_list(t_list *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("%d -> ", *((int *)lst -> content));
		lst = lst -> next;
	}
	printf("NULL");
}

int main()
{
    t_list *head = malloc(sizeof(t_list));
    int initial_content = 10;
    head->content = &initial_content;
    head->next = NULL;

    // Print the original list
    printf("Original list:\n");
    print_list(head);

    // Create a new node
    t_list *new_node = malloc(sizeof(t_list));
    int new_content = 20;
    new_node->content = &new_content;
    new_node->next = NULL;

    // Add the new node to the front of the list
    ft_lstadd_front(&head, new_node);

    // Print the modified list
    printf("\nList after adding a new node to the front:\n");
    print_list(head);

    // Free the allocated memory for the linked list nodes
    while (head != NULL) {
        t_list *temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}*/