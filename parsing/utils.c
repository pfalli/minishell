/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:31:52 by pfalli            #+#    #+#             */
/*   Updated: 2024/09/02 13:31:52 by pfalli           ###   ########.fr       */
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

void	process_dollar_removal(const char *str, char *new_str, int *indices,
		int len)
{
	int	i;
	int	j;

	i = indices[0];
	j = indices[1];
	if (str[i] == '$' && (i == len - 1 || str[i + 1] == ' '
			|| str[i + 1] == '"'))
	{
		new_str[j] = str[i];
		j++;
	}
	else if (str[i] != '$')
	{
		new_str[j] = str[i];
		j++;
	}
	i++;
	indices[0] = i;
	indices[1] = j;
}

// remove the $ if inside the quotes, or not, but not if alone ("$" or $)
char	*remove_dollar(char *str)
{
	int		indices[2];
	int		len;
	char	*new_str;

	indices[0] = 0;
	indices[1] = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (indices[0] < len)
	{
		process_dollar_removal(str, new_str, indices, len);
	}
	new_str[indices[1]] = '\0';
	return (new_str);
}
