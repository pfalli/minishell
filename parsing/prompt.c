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

#include "../minishell.h"
    
void init_prompt(t_prompt *prompt)
{
    memset(prompt, 0, sizeof(t_prompt));
    prompt->symbols = "<>";
    prompt->whitespace = "\t\r\v ";
    // prompt->quotes = "\'\"";
}
