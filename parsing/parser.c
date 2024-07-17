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

bool parser(t_data *structure, t_prompt *prompt)
{
    t_token_node *token;

    init_prompt(prompt);

    // lexing: tokens(nodes)
    token = lexing(structure, prompt);

    // parsing: structure->tree
    parsing(token, prompt);

    return true;
}


// to build the token list
t_token_node *lexing(t_data *structure, t_prompt *prompt) 
{
    t_token_node    *token;

    token = create_node(structure, prompt); // return head node

    // find token

    // add node to list

    return (token);
}


//to recognize the tokens in a binary tree
t_token *parsing(t_token_node *tokens, t_prompt *prompt)
{
    // init_binary_tree

    // init_command_table
}

int main (int ac, char **av, chart **envp)
{
    while(1)
    {
        show_prompt();
    }
}
