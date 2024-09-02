/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_no_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/08/29 11:00:18 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/29 11:00:18 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection_symbol(char c)
{
	return (c == '<' || c == '>');
}

void	insert_space(char *message, char *new_message, int *indices, int len)
{
	int		i;
	int		j;

	i = indices[0];
	j = indices[1];
	if (i > 0 && message[i - 1] != ' ' && !is_redirection_symbol(message[i
				- 1]))
		new_message[j++] = ' ';
	new_message[j++] = message[i];
	if (i < len - 1 && message[i + 1] != ' ' && !is_redirection_symbol(message[i
				+ 1]))
		new_message[j++] = ' ';
	indices[1] = j;
}

char	*redirection_with_no_space(char *message)
{
	int		len;
	char	*new_message;
	bool	in_quotes;
	int		indices[2];

	len = strlen(message);
	new_message = malloc(len * 2 + 1);
	if (!new_message)
		return (NULL);
	in_quotes = false;
	indices[0] = 0;
	indices[1] = 0;
	while (indices[0] < len)
	{
		if (is_quote(message[indices[0]]))
			in_quotes = !in_quotes;
		if (!in_quotes && is_redirection_symbol(message[indices[0]]))
			insert_space(message, new_message, indices, len);
		else
			new_message[indices[1]++] = message[indices[0]];
		indices[0]++;
	}
	new_message[indices[1]] = '\0';
	return (free(message), new_message);
}
