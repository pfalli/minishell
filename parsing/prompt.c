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
    ft_memset(prompt, 0, sizeof(t_prompt));
    prompt->message = readline(prompt);
    prompt->curr_dir = getcwd(NULL, 0);
    prompt->symbols = "<>|";
    prompt->whitespace = "\t\r\v ";
    prompt->quotes = "\'\"";
    prompt->off_symbols = "!@#$%^&*-+=()[]{}\\|:;,<>/?.";
}

void print_prompt(t_prompt *prompt)
{
    printf(RED "MINISHELL$$ " RESET);
}
