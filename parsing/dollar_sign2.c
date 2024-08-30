/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:53:11 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 13:55:15 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int if_only_spaces(const char *str)
{
    while (*str) {
        if (*str != ' ')
            return 0;
        str++;
    }
    return 1;
}

void init_list_nodes(t_token **head, t_token **current, t_token **new)
{
    *head = NULL;
    *current = NULL;
    *new = NULL;
}

char	*expand_message(char *message, t_data *data)
{
	char	*expanded_message;
	char	*removed;

	if (single_quote(message))
		return (message);
	expanded_message = check_dollar_sign(message, data);
	if (expanded_message)
	{
		free(message);
		message = expanded_message;
	}
	removed = remove_dollar(message); // malloc
	free(message);
	return (removed);
}
