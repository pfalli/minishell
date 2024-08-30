/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:16:31 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 14:16:31 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*string_with_quotes(char *str, const char *delim)
{
	char	*end;
	bool	inside_quote;
	char	quote_char;

	end = str;
	inside_quote = false;
	quote_char = '\0';
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
			break ;
		end++;
	}
	return (end);
}

// old one
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
    char *end = string_with_quotes(str, delim);

    if (*end == '\0')
        last = NULL;
    else
    {
        *end = '\0';
        last = end + 1;
    }

    return (str);
}
// Remove quotes if the string didn't start with a double quote.
// ex: echo hello"world"
void	strip_quotes(char **str)
{
    char	*src;
    char	*dst;
    char	start_quote;

    src = *str;
    dst = *str;
    start_quote = '\0';
    if (*src == '"')
    {
        start_quote = '"';
        src++;
    }
    while (*src)
    {
        if (start_quote != '"' && (*src == '"' || *src == '\''))
        {
            src++;
            continue;
        }
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

// strtok with strip_quotes
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

    char *end = string_with_quotes(str, delim);

    if (*end == '\0')
        last = NULL;
    else
    {
        *end = '\0';
        last = end + 1;
    }
    strip_quotes(&str);
    return (str);
}
