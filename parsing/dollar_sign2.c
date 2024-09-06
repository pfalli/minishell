/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:53:11 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 13:55:15 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_only_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

void	init_list_nodes(t_token **head, t_token **current, t_token **new)
{
	*head = NULL;
	*current = NULL;
	*new = NULL;
}

// change the message for hanlding $ dollar sign
char	*expand_message(char *message, t_data *data)
{
	char	*expanded_message;
	char	*removed;

	if (single_quote(message))
		return (message);
	expanded_message = check_dollar_sign(message, data);
	if (expanded_message)
	{
		free(message);
		message = expanded_message;
	}
	removed = remove_dollar(message);
	free(message);
	return (removed);
}

void	sig_heredoc(int signal)
{
	signal = 130;
	g_signal = signal;
	rl_redisplay();
	rl_done = 1;
	printf("\n");
}

char	*ft_strcpy(char *destination, const char *source)
{
	char	*ptr;

	ptr = destination;
	while (*source != '\0')
	{
		*ptr++ = *source++;
	}
	*ptr = '\0';
	return (destination);
}
