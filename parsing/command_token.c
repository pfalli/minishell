/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:54:31 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/02 10:54:31 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command *create_command_node(char *command)
{
    int length = strlen(command);
    t_command *new_node = malloc(sizeof(t_command));
    if (new_node == NULL)
        return NULL;
    new_node->command = (char *)malloc(sizeof(char) * (length + 1));
    if (new_node->command == NULL)
    {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->command, command);
    // ** calculate word_type **
    new_node->next = NULL;
    return new_node;
}

void append_command_node(t_command **head, t_command **current, t_command *new_node)
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

t_command *create_command_list(char *command)
{
    t_command *head = NULL;
    t_command *current = NULL;
    int i = 0;

    while (command)
    {
        t_command *new_node = create_command_node(command);
        if (new_node == NULL)
        {
            while (head != NULL) // create a free_function for freeing at the end
            {
                t_command *temp = head;
                head = head->next;
                free(temp->command);
                free(temp);
            }
            return NULL;
        }
        append_command_node(&head, &current, new_node);
        i++;
    }

    return head;
}

void free_command_list(t_command *head)
{
    while (head != NULL)
    {
        t_command *temp = head;
        head = head->next;
        free(temp->command);
        free(temp);
    }
}