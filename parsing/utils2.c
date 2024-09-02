/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:58:29 by pfalli            #+#    #+#             */
/*   Updated: 2024/09/02 14:47:54 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*s;
	const char	*a;
	bool		found;

	s = str;
	while (*s)
	{
		a = accept;
		found = false;
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

t_type	search_type(char *word)
{
	t_type	type;

	type = 0;
	if (strcmp(word, "<") == 0)
		type = REDIRECTION_IN;
	else if (strcmp(word, ">") == 0)
		type = REDIRECTION_OUT;
	else if (strcmp(word, ">>") == 0)
		type = APPEND;
	else if (strcmp(word, "<<") == 0)
		type = HEREDOC;
	return (type);
}

void	initialize_redirection_pointers(t_redirection **redir_head,
		t_redirection **redir_current)
{
	*redir_head = NULL;
	*redir_current = NULL;
}

bool	single_quote(const char *str)
{
	bool	single_quotes;

	single_quotes = false;
	while (*str)
	{
		if (*str == '\'')
			single_quotes = !single_quotes;
		else if (*str == '$' && single_quotes)
			return (true);
		str++;
	}
	return (false);
}
