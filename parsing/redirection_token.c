/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:36:12 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 14:36:12 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*create_redirection_node(char *file_name, t_type type)
{
	t_redirection	*new_node;

	new_node = malloc(sizeof(t_redirection));
	if (new_node == NULL)
		return (NULL);
	new_node->file_name = strdup(file_name);
	if (new_node->file_name == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	append_redirection_node(t_redirection **head, t_redirection **current,
		t_redirection *new_node)
{
	if (*head == NULL)
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

t_redirection	*create_redirection_list(t_token *new, t_prompt *prompt,
		char *message)
{
	t_redirection	*redir_head;
	t_redirection	*redir_current;
	char			*word;
	bool			redirection;
	t_type			type;
	t_redirection	*new_redir;

	redir_head = NULL;
	redir_current = NULL;
	word = ft_strtok_copy(message, prompt->whitespace);
	redirection = false;
	while (word != NULL)
	{
		if (strcmp(word, ">") == 0 || strcmp(word, "<") == 0 || strcmp(word,
				">>") == 0 || strcmp(word, "<<") == 0)
		{
			redirection = true;
			type = search_type(word);
		}
		else if (redirection)
		{
			new_redir = create_redirection_node(word, type);
			append_redirection_node(&redir_head, &redir_current, new_redir);
			redirection = false;
		}
		word = ft_strtok_copy(NULL, prompt->whitespace);
	}
	new->redirection = redir_head;
	return (redir_head);
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
