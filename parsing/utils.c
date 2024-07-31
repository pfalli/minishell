/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:13:56 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/22 10:13:56 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *ft_strtok(char *str, const char *delim)
{
    static char *last;
    if (str == NULL)
        str = last;
    if (str == NULL)
        return NULL;

    // Skip leading delimiters
    str += ft_strspn(str, delim);
    if (*str == '\0')
        return NULL;

    // Find the end of the token
    char *end = str + ft_strcspn(str, delim);
    if (*end == '\0')
    {
        last = NULL;
    }
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

    // Skip leading delimiters
    str += ft_strspn(str, delim);
    if (*str == '\0')
        return NULL;

    // Find the end of the token
    char *end = str + ft_strcspn(str, delim);
    if (*end == '\0')
    {
        last = NULL;
    }
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

size_t ft_strcspn(const char *str, const char *reject)
{
    const char *s = str;
    while (*s)
    {
        const char *r = reject;
        while (*r)
        {
            if (*s == *r)
                return s - str;
            r++;
        }
        s++;
    }
    return s - str;
}

int count_word(const char *str)
{
    int count = 0;
    bool in_token = false;

    while (*str)
    {
        if (*str == ' ')
        {
            in_token = false;
        }
        else if (!in_token)
        {
            in_token = true;
            count++;
        }
        str++;
    }
    return count;
}

char **ft_split(const char *str, char delimiter)
{
    size_t count = 0;
    const char *temp = str;
    while (*temp)
    {
        if (*temp == delimiter)
            count++;
        temp++;
    }

    char **result = malloc((count + 2) * sizeof(char *));
    if (!result)
        return NULL;

    size_t idx = 0;
    const char *start = str;
    while (*str)
    {
        if (*str == delimiter)
        {
            size_t len = str - start;
            result[idx] = malloc(len + 1);
            strncpy(result[idx], start, len);
            result[idx][len] = '\0';
            idx++;
            start = str + 1;
        }
        str++;
    }
    result[idx] = strdup(start);
    result[idx + 1] = NULL;

    return result;
}