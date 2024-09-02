/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
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

bool	is_redirection_operator(const char *word)
{
	return (strcmp(word, ">") == 0 || strcmp(word, "<") == 0 || strcmp(word,
			">>") == 0 || strcmp(word, "<<") == 0);
}

void	process_redirection(t_redirection **redir_head,
		t_redirection **redir_current, char *word, t_type type)
{
	t_redirection	*new_redir;

	new_redir = create_redirection_node(word, type);
	append_redirection_node(redir_head, redir_current, new_redir);
}

t_redirection	*create_redirection_list(t_token *new, t_prompt *prompt,
		char *message)
{
	t_redirection	*redir_head;
	t_redirection	*redir_current;
	char			*word;
	bool			redirection;
	t_type			type;

	redirection = false;
	initialize_redirection_pointers(&redir_head, &redir_current);
	word = ft_strtok_copy(message, prompt->whitespace);
	while (word != NULL)
	{
		if (is_redirection_operator(word))
		{
			redirection = true;
			type = search_type(word);
		}
		else if (redirection)
		{
			process_redirection(&redir_head, &redir_current, word, type);
			redirection = false;
		}
		word = ft_strtok_copy(NULL, prompt->whitespace);
	}
	new->redirection = redir_head;
	return (redir_head);
}
