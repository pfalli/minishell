/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:54:43 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/08 09:54:43 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_quote(char c)
{
    return c == '"' || c == '\'';
}

char *find_token_end(char *str, const char *delim)
{
    char *end = str;
    bool inside_quote = false;
    char quote_char = '\0';

    while (*end)
    {
        if (is_quote(*end))
        {
            if (inside_quote && *end == quote_char)
                inside_quote = false;
            else if (!inside_quote)
            {
                inside_quote = true;
                quote_char = *end;
            }
        }
        else if (!inside_quote && ft_strchr(delim, *end))
            break;
        end++;
    }
    return end;
}



char *ft_strtok(char *str, const char *delim)
{
    static char *last;
    if (str == NULL)
        str = last;
    if (str == NULL)
        return NULL;

    str += ft_strspn(str, delim);
    if (*str == '\0')
        return NULL;

    char *end = find_token_end(str, delim); // for quoted substring

    if (*end == '\0')
        last = NULL;
    else
    {
        *end = '\0';
        last = end + 1;
    }

    return str;
}


char *ft_strtok_copy(char *str, const char *delim)
{
    static char *last;
    if (str == NULL)
        str = last;
    if (str == NULL)
        return NULL;

    str += ft_strspn(str, delim);
    if (*str == '\0')
        return NULL;

    char *end = find_token_end(str, delim);

    if (*end == '\0')
        last = NULL;
    else
    {
        *end = '\0';
        last = end + 1;
    }

    return str;
}


size_t ft_strspn(const char *str, const char *accept)
{
    const char *s = str;
    while (*s)
    {
        const char *a = accept;
        bool found = false;
        while (*a)
        {
            if (*s == *a)
            {
                found = true;
                break;
            }
            a++;
        }
        if (!found)
            break;
        s++;
    }
    return s - str;
}
