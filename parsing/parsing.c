/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:43:52 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 11:43:52 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_multi_command(t_token *new, t_prompt *prompt)
{
	char	*value_copy;
	char	*word;
	bool	redirection;

	redirection = false;
	value_copy = strdup(new->value);
	if (!value_copy)
		return (NULL);
	if (!initialize_multi_arrays(new, value_copy))
		return (NULL);
	word = ft_strtok_copy(value_copy, prompt->whitespace);
	while (word != NULL)
	{
		if (is_redirection_operator(word))
			redirection = true;
		else if (redirection)
			redirection = false;
		else
			new->multi_command[new->cmd_count++] = strdup(word);
		word = ft_strtok_copy(NULL, prompt->whitespace);
	}
	new->multi_command[new->cmd_count] = NULL;
	free(value_copy);
	return (new);
}

t_token	*create_linked_list(t_prompt *prompt, char *message)
{
	t_token	*head;
	t_token	*new;
	t_token	*current;
	char	*save_prompt_message;
	char	*token;

	save_prompt_message = strdup(message);
	token = ft_strtok(save_prompt_message, "|");
	init_list_nodes(&head, &current, &new);
	while (token != NULL)
	{
		new = create_token(token);
		if (new == NULL)
		{
			ft_free_token_list(new);
			return (NULL);
		}
		append_node(&head, &current, new);
		init_multi_command(new, prompt);
		create_redirection_list(new, prompt, token);
		token = ft_strtok(NULL, "|");
	}
	free(save_prompt_message);
	return (head);
}

void	append_node(t_token **head, t_token **current, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		*current = new;
	}
	else
	{
		(*current)->next = new;
		*current = new;
	}
}

t_token	*create_token(char *word)
{
	t_token	*new_token;
	int		i;
	int		length;

	i = 0;
	length = strlen(word);
	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = (char *)malloc(sizeof(char) * (length + 1));
	if (new_token->value == NULL)
	{
		free(new_token);
		return (NULL);
	}
	while (i < length)
	{
		new_token->value[i] = word[i];
		i++;
	}
	new_token->next = NULL;
	new_token->cmd_count = 0;
	return (new_token);
}

bool	initialize_multi_arrays(t_token *new, char *value_copy)
{
	new->word_count = count_word(new->value);
	new->multi_command = malloc(sizeof(char *) * (new->word_count + 1));
	if (!new->multi_command)
	{
		free(value_copy);
		return (false);
	}
	return (true);
}
