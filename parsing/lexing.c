/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:03:04 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/16 13:03:04 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token *create_linked_list(t_prompt *prompt)
{
    t_token *head = NULL;
    t_token *new = NULL;
    t_token *current = NULL;
    char *word = strtok(prompt->message, " ");
    
    while(word != NULL)
    {  
        new = create_token(word);
        if (!new)
        {
            ft_free_token_list(head);
            return NULL;
        }
	    if (head == NULL)
        {
            head = new;
            current = new;
        }
        else
        {
            current->next = new;
            new->prev = current;
            current = new;
        }
        word = strtok(NULL, " ");
    }
    return(head);
}

t_token *create_token(char *word)
{
    t_token *new_token;
    int i = 0;
    int length = strlen(word);

    new_token = malloc(sizeof(t_token));
    if(new_token == NULL)
        return NULL;
    new_token->value = (char *)malloc(sizeof(char) * (length + 1));
    if (new_token->value == NULL)
	{
		free(new_token);
		return (NULL);
	}
    while (i < length)
	{
		new_token->value[i] = word[i];
		i++;
	}
    new_token->value[i] = 0;
    new_token->next = NULL;
    new_token->prev = NULL;
    new_token->type = search_token_type(word);
    return(new_token);
}

t_type search_token_type(char *word)
{
    t_type type;

    if(strcmp(word, "|") == 0)
        type = PIPE;
    else if(strcmp(word, "<") == 0 || strcmp(word, ">") == 0)
        type = REDIRECTION;
    else
        type = WORD;
    return(type);
}

void	ft_free_token_list(t_token *token_list)
{
	t_token	*token_list_holder;

	if (!token_list)
		return ;
	while (token_list)
	{
		free(token_list->value);
		token_list_holder = token_list;
		token_list = token_list->next;
		free(token_list_holder);
	}
	return ;
}

// Recursive function to print the tree
void print_tree(t_tree* tree_node) // I was't allocating properly the tree_node in create_tree_node
{
    int i = 0;

    if (tree_node == NULL)
        return;
    while (i < tree_node->num_tokens)
    {
        printf("Node[%d]: %s\n", i, tree_node->value[i]);
        printf("    type: %d\n", tree_node->type);
        printf("    num_tokens: %i\n", tree_node->num_tokens);
        i++;
    }
    

    printf("*Left Child*\n");
    printf("Node[%d]: %s\n", i, tree_node->left->value[0]);
    printf("    type: %d\n", tree_node->left->type);
    printf("    num_tokens: %i\n", tree_node->left->num_tokens);
    
    
    printf("*Right Child*\n");
    printf("Node[%d]: %s\n", i, tree_node->right->value[0]);
    printf("    type: %d\n", tree_node->right->type);
    printf("    num_tokens: %i\n", tree_node->right->num_tokens);
    
}



int main()
{
    t_prompt prompt;
    t_token *token_list;
    t_token *current_token;
    t_tree *tree_node;

    int i = 0;

    init_prompt(&prompt);

    token_list = create_linked_list(&prompt);

    current_token = token_list;
    while (current_token != NULL)
    {
        printf("Token[%i]: %s --> type: %d\n", i, current_token->value, current_token->type);
        current_token = current_token->next;
        i++;
    }

    tree_node = create_tree(token_list);
    printf("***Binary Tree***\n");
    print_tree(tree_node);

    return 0;
}