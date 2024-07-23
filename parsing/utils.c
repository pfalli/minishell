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
    static char *last = NULL;
    
    if (str == NULL)
        str = last;
    if (str == NULL || *str == '\0')
        return NULL;
    while (*str && strchr(delim, *str))
        ++str;
    if (*str == '\0')
        return NULL;
    char *token = str;
    while (*str && !strchr(delim, *str))
        ++str;
    if (*str == '\0')
        last = NULL;
    else
    {
        *str = '\0';
        last = str + 1;
    }
    return token;
}


//  int main()
//  {
//      char str[] = "ciao sono piero 1 2 3 !";
//      char *token;
//  
//      token = ft_strtok(str, " ");
//      while (token != NULL)
//      {
//          printf("%s\n", token);
//          token = ft_strtok(NULL, " ");
//      }
//      return 0;
//  }
