/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:50:45 by atamas            #+#    #+#             */
/*   Updated: 2023/12/01 17:32:04 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* #include <stdio.h>

int main(void)
{
    // Create a new node
    t_list *new_node = malloc(sizeof(t_list));

    // Initialize the new node
    new_node->content = "Hello, World!";
    new_node->next = NULL;

    // Create a list pointer
    t_list *my_list = NULL;

    // Add the new node to the front of the list
    ft_lstadd_front(&my_list, new_node);

    // Print the content of the first node in the list
    if (my_list)
    {
        printf("First node content: %s\n", (char *)my_list->content);
    }
    else
    {
        printf("List is empty.\n");
    }

    // Don't forget to free the allocated memory
    free(new_node);

    return 0;
} */