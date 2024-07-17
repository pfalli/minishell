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

t_token_node *create_node(t_data *structure, t_prompt *prompt)
{
    t_token_node *node;

    node = (t_token_node*)malloc(sizeof(t_token_node));
    if(!token)
        return NULL;
    node->token = init_token_struct();
    node->next = NULL;
    return(node);
}

t_token *init_token_struct(t_data *structure, t_prompt *prompt)
{
    t_token token;
    t_type type;

    type = search_token_type(prompt);
    if (type == WORD)
        // full token
    else if (type == PIPE)
        // pipe operation
    else if (type == REDIRECTION)
        // redirect token
    else
        // error
    return(token);
}

t_type search_token_type(t_prompt *prompt)
{
    t_type type;

    if(prompt->ptr_prompt == NULL)
        prompt->ptr_prompt == prompt->message;
    if(strchr(prompt->symbols, prompt->message))
    {
        if(prompt->message == '|') // multiple pipes
            type = PIPE;
        else if(prompt->message == '<' || prompt->message == '>') // multuiple redirections
            type == REDIRECTION;
    }
    else
        type = WORD; // function to recognize command, argument, ...
    return(type);
}