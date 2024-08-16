/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:39:00 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/08 16:39:00 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "parsing.h"

char *extract_var_name(const char *str, int *index)
{
    char var_name[256];
    int j = 0;

    while (str[*index] && (isalnum(str[*index]) || str[*index] == '_'))
        var_name[j++] = str[(*index)++];
    var_name[j] = '\0';
    return ft_strdup(var_name);
}

char *replace_var_with_value(const char *str, const char *var_value, int start, int var_len)
{
    int new_len = strlen(str) + strlen(var_value) - var_len;
    char *new_str = malloc(new_len + 1);

    if (!new_str)
        return NULL;
    ft_strlcpy(new_str, str, start - var_len + 1);
    strcat(new_str, var_value);
    strcat(new_str, &str[start]);
    return new_str;
}

char *replace_variable(char *str, int *i)
{
    int var_start = *i;
    char *var_name = extract_var_name(str, i);
    if (!var_name)
        return free_and_return_null(str);
    char *var_value = getenv(var_name);
    free(var_name);
    if (!var_value)
        return str;
    char *new_str = replace_var_with_value(str, var_value, *i, *i - var_start);
    if (!new_str)
        return free_and_return_null(str);
    free(str);
    return new_str;
}

char *check_dollar_sign(char *command)
{
    char *str = ft_strdup(command);
    if (!str)
        return NULL;
    for (int i = 0; str[i];)
    {
        if (str[i] == '$')
        {
            i++;
            str = replace_variable(str, &i);
            if (!str)
                return NULL;
        }
        else
            i++;
    }
    return str;
}

char *expand_message(char *message)
{
    char *expanded_message = check_dollar_sign(message);
    if (expanded_message)
    {
        free(message);
        message = expanded_message;
    }
    return message;
}
