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

// Function to check if a character is a quote
bool is_quote(char c)
{
    return c == '"' || c == '\'';
}

char *find_token_end(char *str, const char *delim)
{
    char *end = str;
    bool in_quote = false;
    char quote_char = '\0';

    while (*end)
    {
        if (is_quote(*end))
        {
            if (in_quote && *end == quote_char)
                in_quote = false;
            else if (!in_quote)
            {
                in_quote = true;
                quote_char = *end;
            }
        }
        else if (!in_quote && strchr(delim, *end))
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

    // Skip leading delimiters
    str += ft_strspn(str, delim);
    if (*str == '\0')
        return NULL;

    // Find the end of the token
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

void print_token_details(t_token *token_list)
{
    int i = 0;
    int j;

    t_token *current_token = token_list;
    while (current_token != NULL)
    {
        printf("Token_value[%i]: %s\n", i, current_token->value);

        if (current_token->multi_command == NULL)
            printf("ERROR MULTI COMMAND\n");
        printf("  Commands:\n");
        j = 0;
        while (j < current_token->cmd_count)
        {
            printf("    Command[%d]: %s\n", j, current_token->multi_command[j]);
            j++;
        }
        if (current_token->multi_files == NULL)
            printf("ERROR MULTI FILE\n");
        printf("  Files:\n");
        j = 0;
        while (j < current_token->file_count)
        {
            printf("    File[%d]: %s\n", j, current_token->multi_files[j]);
            j++;
        }
        printf(" *** redirection_list***\n");
        print_redirection_list(current_token->redirection);
        current_token = current_token->next;
        i++;
    }
}

const char *type_to_string(enum s_type type)
{
    switch (type)
    {
    case START:
        return "START";
    case REDIRECTION_IN:
        return "REDIRECTION_IN";
    case REDIRECTION_OUT:
        return "REDIRECTION_OUT";
    case APPEND:
        return "APPEND";
    case HEREDOC:
        return "HEREDOC";
    case SIMPLE_CMD:
        return "SIMPLE_CMD";
    case BUILTIN_CMD:
        return "BUILTIN_CMD";
    case ARGUMENT:
        return "ARGUMENT";
    case FILE_EOF:
        return "FILE_EOF";
    default:
        return "UNKNOWN";
    }
}