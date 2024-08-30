/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_no_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:00:18 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/29 11:00:18 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection_symbol(char c)
{
    return (c == '<' || c == '>');
}
void	insert_space(char *message, char *new_message, int *i, int *j, int len)
{
    if (*i > 0 && message[*i - 1] != ' ' && !is_redirection_symbol(message[*i - 1]))
        new_message[(*j)++] = ' ';
    new_message[(*j)++] = message[*i];
    if (*i < len - 1 && message[*i + 1] != ' ' && !is_redirection_symbol(message[*i + 1]))
        new_message[(*j)++] = ' ';
}

char	*redirection_with_no_space(char *message)
{
    int		len;
    char	*new_message;
    bool	in_quotes;
    int		i;
    int		j;

    len = strlen(message);
    new_message = malloc(len * 2 + 1);
    if (!new_message)
        return (NULL);
    in_quotes = false;
    j = 0;
    i = 0;
    while (i < len)
    {
        if (is_quote(message[i]))
            in_quotes = !in_quotes;
        if (!in_quotes && is_redirection_symbol(message[i]))
            insert_space(message, new_message, &i, &j, len);
        else
            new_message[j++] = message[i];
        i++;
    }
    new_message[j] = '\0';
    free(message);
    return (new_message);
}
