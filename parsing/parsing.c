/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:03:04 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/16 13:03:04 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *check_syntax(char *word)
{
    char *new;
    size_t len;

    if (!word || (len = ft_strlen(word)) < 2)
        return NULL;
    new = (char *)malloc(len - 1);
    if (!new)
        return NULL;
    strncpy(new, word + 1, len - 2);
    new[len - 2] = '\0';

    return (ft_strdup(new));
}

t_token *init_multi_arrays(t_token *new, t_prompt *prompt)
{
    char *value_copy = strdup(new->value);
    char *word;
    bool redirection = false;

    if (!value_copy)
        return NULL;
    if (!initialize_multi_arrays(new, value_copy))
        return(NULL);
    word = ft_strtok_copy(value_copy, prompt->whitespace);
    while (word != NULL)
    {
        if (strcmp(word, ">") == 0 || strcmp(word, "<") == 0 || strcmp(word, ">>") == 0 || strcmp(word, "<<") == 0 )
            redirection = true;
        else if (redirection)
        {
            new->multi_files[new->file_count++] = strdup(word);
            redirection = false;
        }
        else
            new->multi_command[new->cmd_count++] = strdup(word);
        word = ft_strtok_copy(NULL, prompt->whitespace);
    }
    new->multi_command[new->cmd_count] = NULL;
    new->multi_files[new->file_count] = NULL;
    free(value_copy);
    return new;
}


t_token *create_linked_list(t_prompt *prompt, char *message) // a token is everything between the PIPE |
{
    t_token *head = NULL;
    t_token *new = NULL;
    t_token *current = NULL;
    char *save_prompt_message = strdup(message);
    char *token = ft_strtok(save_prompt_message, "|");
    int i = 0;
    
    while(token != NULL)
    {
        new = create_token(token);
        if (new == NULL)
        {
            ft_free_token_list(new);
            return NULL;
        }
        append_node(&head, &current, new);
        init_multi_arrays(new, prompt);

        create_redirection_list(new, prompt, token);

        token = ft_strtok(NULL, "|");
        i++;
    }
    free(save_prompt_message);
    return(head);
}

void append_node(t_token **head, t_token **current, t_token *new)
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

t_token *create_token(char *word)
{
    t_token *new_token;
    int i = 0;
    int length = strlen(word);

    new_token = malloc(sizeof(t_token));
    if(new_token == NULL)
        return NULL;
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
    new_token->value[i] = 0;
    new_token->next = NULL;
    new_token->file_count = 0;
    new_token->cmd_count = 0;
    return(new_token);
}


bool initialize_multi_arrays(t_token *new, char *value_copy)
{
    new->word_count = count_word(new->value);
    new->multi_command = malloc(sizeof(char *) * (new->word_count + 1));
    new->multi_files = malloc(sizeof(char *) * (new->word_count + 1));

    if (!new->multi_command || !new->multi_files)
    {
        free(value_copy);
        return false;
    }
    return true;
}

void minishell_loop(t_prompt *prompt, t_token **token_list, t_data *data)
{
    char *message;

    while (1)
    {
        if (g_signal_received)
        {
            g_signal_received = 0;
            continue;
        }
        message = readline(RED "MINISHELL$$ " RESET);
        if (message == NULL)
        {
            // free(message);
            printf("exit (detected Ctrl + D)\n");
            break ;
        }
        if(message)
            add_history(message);
        message = expand_message(message, data);

        *token_list = create_linked_list(prompt, message);
        print_token_details(*token_list);
		command_processor(*token_list, data);
        if (message)
			free(message);
        ft_free_token_list(*token_list);
    }
}

//  int main()
//  {
//      t_prompt prompt;
//      t_token *token_list = NULL;// 

//      init_prompt(&prompt);//   

//      minishell_loop(&prompt, &token_list);//   

//      printf("prompt->message: %s\n", prompt.message);
//      ft_free_token_list(token_list);
//      free_prompt(&prompt);
//      free_readline();
//      return 0;
//  }