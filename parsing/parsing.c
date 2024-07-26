/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:22:12 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/15 13:22:12 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void parser(t_token *token_list, t_prompt *prompt)
{
    t_token *token_list;

    init_prompt(prompt);

    token_list = lexing(prompt);

    // parsing: structure->tree
    //parsing(token, prompt);
}


// to build the token list
t_token *lexing(t_prompt *prompt) 
{
    t_token    *token_list;

    token_list = create_linked_list(prompt);
    
    // 

    // 

    return (token_list);
}


//  //to recognize the tokens in a binary tree
//  t_token *parsing(t_token_node *tokens, t_prompt *prompt)
//  {
//      // init_binary_tree
//  
//      // init_command_table
//  }
