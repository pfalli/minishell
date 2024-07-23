/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:16:41 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/16 09:16:41 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
    
void init_prompt(t_prompt *prompt)
{
    memset(prompt, 0, sizeof(t_prompt));
    prompt->message = readline(RED "MINISHELL$$ " RESET);
    prompt->curr_dir = getcwd(NULL, 0);
    prompt->symbols = "<>|";
    prompt->whitespace = "\t\r\v ";
    prompt->quotes = "\'\"";
    prompt->off_symbols = "!@#$%^&*-+=()[]{}\\|:;,<>/?.";
    

    //  // Debug
    //  printf("Prompt message: %s\n", prompt->message);
    //  printf("Current directory: %s\n", prompt->curr_dir);
    //  printf("Symbols: %s\n", prompt->symbols);
    //  printf("Whitespace: %s\n", prompt->whitespace);
    //  printf("Quotes: %s\n", prompt->quotes);
    //  printf("Off symbols: %s\n", prompt->off_symbols);
}
