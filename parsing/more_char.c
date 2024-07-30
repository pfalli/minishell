/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:55:05 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/30 12:44:34 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int more_char(t_token *token_list)
{
    
}

int enlarge_token_list(t_token **token_list, t_prompt *prompt)
{
    t_token *token;
    char *temp_value = NULL;
    
    token = *token_list;
    if (!token)
        return(1);
    while (token)
    {
        if (token->type == WORD)
        {
            temp_value = token->value;
            token->value = more_char(token->value);
            if (temp_value != NULL)
                free(temp_value);
        }
        token = token->next;
    }
    return 0;
}
