/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:48:12 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/02 10:48:12 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_red_token *create_redirection_node(char *file_name)
{
    t_redirection_token *new_node = malloc(sizeof(t_redirection_token));
    if (new_node == NULL)
        return NULL;
    new_node->file_name = strdup(file_name); // Use strdup to allocate and copy the string
    if (new_node->file_name == NULL)
    {
        free(new_node);
        return NULL;
    }
    // **calculate redirection_type**
    new_node->next = NULL;
    return new_node;
}

void append_redirection_node(t_redirection_token **head, t_redirection_token **current, t_redirection_token *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        *current = new_node;
    }
    else
    {
        (*current)->next = new_node;
        *current = new_node;
    }
}

t_redirection_token *create_redirection_list(char *file_name)
{
    t_redirection_token *head = NULL;
    t_redirection_token *current = NULL;
    int i = 0;

    while (file_name)
    {
        t_redirection_token *new_node = create_redirection_node(file_name);
        if (new_node == NULL)
        {
            while (head != NULL)// create a free_function for freeing at the end
            {
                t_redirection_token *temp = head;
                head = head->next;
                free(temp->file_name);
                free(temp);
            }
            return NULL;
        }
        append_redirection_node(&head, &current, new_node);
        i++;
    }

    return head;
}