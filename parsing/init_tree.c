/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:28:02 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/25 11:28:02 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int count_tokens_list(t_token *token_list)
{
    int count = 0;
    t_token *temp;

    temp = token_list;
    if (temp->type == PIPE)
        count++;
    while (temp != NULL && temp->type != PIPE)
    {
        count++;
        temp = temp->next;
    }
    return(count);
}

t_tree *create_tree_node(t_token *token_list, int num_tokens)
{
    t_tree *node;
    int index = 0;

    node = malloc(num_tokens);
    node->type = TREE_CMD;
    if (token_list->type == PIPE)
        node->type = TREE_PIPE;
    while(num_tokens-- > 0)
    {
        if (token_list->value)
        {
            node->value[index] = strdup(token_list->value);
        }
        index++;
        token_list = token_list->next;
    }
    return(node);

}

t_tree *create_tree(t_token *token_list)
{
    t_tree *new_node;
    t_tree *tree_node = NULL;
    int num_tokens;

    while (token_list != NULL)
    {
        num_tokens = count_tokens_list(token_list);
        new_node = create_tree_node(token_list, num_tokens);
        new_node->num_tokens = num_tokens;
        if (tree_node == NULL) // start
            tree_node = new_node;
        else if (token_list->type == PIPE)
        {
            new_node->left = tree_node;
            tree_node = new_node;
        }
        else
            tree_node->right = new_node;
        while (num_tokens--)
            token_list = token_list->next;
        new_node = NULL;
    }
    return(tree_node);
}


