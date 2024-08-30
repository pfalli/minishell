/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:10:44 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 14:14:30 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end != '\0')
		dest_end++;
	while (*src != '\0')
	{
		*dest_end = *src;
		dest_end++;
		src++;
	}
	*dest_end = '\0';
	return (dest);
}

int	count_word(const char *str)
{
	int		count;
	bool	in_token;

	count = 0;
	in_token = false;
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
	return (count);
}

void	*free_and_return_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

void process_dollar_removal(const char *str, char *new_str, int *i, int *j, int len)
{
    if (str[*i] == '$' && (*i == len - 1 || str[*i + 1] == ' ' || str[*i + 1] == '"'))
	{
        new_str[*j] = str[*i];
        (*j)++;
    }
	else if (str[*i] != '$')
	{
        new_str[*j] = str[*i];
        (*j)++;
    }
    (*i)++;
}

// changed for case: echo $ and echo "$"
char	*remove_dollar(char *str)
{
    int		i;
    int		len;
    char	*new_str;
    int		j;

    i = 0;
    if (!str)
        return (NULL);
    len = ft_strlen(str);
    new_str = (char *)malloc(len + 1);
    if (!new_str)
        return (NULL);
    j = 0;
    while (i < len)
	{
        process_dollar_removal(str, new_str, &i, &j, len);
    }
    new_str[j] = '\0';
    return (new_str);
}

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*s;

	s = str;
	while (*s)
	{
		const char	*a = accept;
		bool	found = false;
		while (*a)
		{
			if (*s == *a)
			{
				found = true;
				break ;
			}
			a++;
		}
		if (!found)
			break ;
		s++;
	}
	return (s - str);
}
