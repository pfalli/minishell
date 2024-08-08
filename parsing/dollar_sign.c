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

char *check_dollar_sign(char *command)
{
    char *str = ft_strdup(command);
    if (!str)
        return NULL;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            int var_start = i;
            char *var_name = extract_var_name(str, &i);
            if (!var_name)
                return free_and_return_null(str);
            char *var_value = getenv(var_name);
            free(var_name);
            if (var_value)
            {
                char *new_str = replace_var_with_value(str, var_value, i, i - var_start);
                if (!new_str)
                    return free_and_return_null(str);
                free(str);
                str = new_str;
            }
        }
        else
            i++;
    }
    return str;
}

//  char *check_dollar_sign(char *command)
//  {
//      char *str = ft_strdup(command);
//      if (!str)
//          return NULL;
//  
//      int i = 0;
//      while (str[i])
//      {
//          if (str[i] == '$')
//          {
//              i++;
//              // Extract the variable name
//              char var_name[256]; // Assuming variable names are less than 256 characters
//              int j = 0;
//              while (str[i] && (isalnum(str[i]) || str[i] == '_'))
//              {
//                  var_name[j++] = str[i++];
//              }
//              var_name[j] = '\0';
//  
//              // Get the value of the environment variable
//              char *var_value = getenv(var_name);
//              if (var_value)
//              {
//                  // Replace $VAR with its value
//                  char *new_str = malloc(strlen(str) + strlen(var_value) - j + 1);
//                  if (!new_str)
//                  {
//                      free(str);
//                      return NULL;
//                  }
//                  ft_strlcpy(new_str, str, i - j); // Copy part before $
//                  strcat(new_str, var_value); // Append the variable value
//                  strcat(new_str, &str[i]); // Append the rest of the original string
//                  free(str);
//                  str = new_str;
//              }
//          }
//          else
//          {
//              i++;
//          }
//      }
//      return str;
//  }