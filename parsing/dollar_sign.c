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

char *extract_var_name(const char *str, int *index)
{
    char var_name[256];
    int j = 0;

    while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
        var_name[j++] = str[(*index)++];
    var_name[j] = '\0';
    return (ft_strdup(var_name));
}


char *replace_var_with_value(const char *str, const char *var_value, int start, int var_len)
{
    int new_len;
    char *new_str;

    //  if (str[start - var_len - 1] == '"')
    //  {
    //      start--;
    //      var_len--;
    //  }
    //  if (str[start - var_len] == '$')
    //      var_len--;
    //  if (var_value[0] == '"' && var_value[ft_strlen(var_value) - 1] == '"')
    //  {
    //      var_value++;
    //      var_len -= 2;
    //  }
    new_len = ft_strlen(str) + ft_strlen(var_value) - var_len;
    new_str = malloc(new_len + 1);
    if (!new_str)
        return NULL;
    ft_strlcpy(new_str, str, start - var_len + 1);
    ft_strcat(new_str, var_value);
    ft_strcat(new_str, &str[start]);
    return (new_str);
}

//  char *get_env_value(const char *var_name, t_data *data)
//  {
//      int i;
//      size_t len;
//  
//      i = 0;
//      len = ft_strlen(var_name);
//      while (data->envp[i])
//      {
//          if (ft_strncmp(data->envp[i], var_name, len) == 0 && data->envp[i][len] == '=')
//              return (data->envp[i] + len + 1);
//          i++;
//      }
//      return (NULL);
//  }


char *replace_variable(char *str, int *i) // allocated from extract_var_name
{
    int var_start;
    char *var_name;

    var_start = *i;
    var_name = extract_var_name(str, i);
    if (!var_name)
        return free_and_return_null(str);
    char *var_value;
    var_value = getenv(var_name); // i have to take it from envp???
    free(var_name);
    if (!var_value)
        return (str);
    //printf("variable: %s\n", var_value);
    char *new_str;
    new_str = replace_var_with_value(str, var_value, *i, *i - var_start);
    if (!new_str)
        return free_and_return_null(str);
    free(str);
    return (new_str);
}


char *check_dollar_sign(char *command)
{
    char *str;
    int i;

    i = 0;
    str = ft_strdup(command);
    if (!str)
        return NULL;
    while (str[i])
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
    return (str);
}


char *expand_message(char *message)
{
    char *expanded_message;

    expanded_message = check_dollar_sign(message);
    if (expanded_message)
    {
        free(message);
        message = expanded_message;
    }
    //printf("dollar sign: %s\n", message);
    return (message);
}
