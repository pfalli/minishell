/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:13:56 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/22 10:13:56 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int count_word(const char *str)
{
    int count = 0;
    bool in_token = false;

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
    return count;
}



void print_token_details(t_token *token_list)
{
    int i = 0;
    int j;

    t_token *current_token = token_list;
    while (current_token != NULL)
    {
        printf("Token_value[%i]: %s\n", i, current_token->value);

        if (current_token->multi_command == NULL)
            printf("ERROR MULTI COMMAND\n");
        printf("  Commands:\n");
        j = 0;
        while (j < current_token->cmd_count)
        {
            printf("    Command[%d]: %s\n", j, current_token->multi_command[j]);
            j++;
        }
        if (current_token->multi_files == NULL)
            printf("ERROR MULTI FILE\n");
        printf("  Files:\n");
        j = 0;
        while (j < current_token->file_count)
        {
            printf("    File[%d]: %s\n", j, current_token->multi_files[j]);
            j++;
        }
        printf(" *** redirection_list***\n");
        print_redirection_list(current_token->redirection);
        current_token = current_token->next;
        i++;
    }
}

void print_redirection_list(t_redirection *redir_list)
{
    t_redirection *current = redir_list;
    while (current != NULL)
    {
        printf("    File_name: %s, Type: %s\n", current->file_name, type_to_string(current->type));
        current = current->next;
    }
}

const char *type_to_string(enum s_type type)
{
    switch (type)
    {
    case START:
        return "START";
    case REDIRECTION_IN:
        return "REDIRECTION_IN";
    case REDIRECTION_OUT:
        return "REDIRECTION_OUT";
    case APPEND:
        return "APPEND";
    case HEREDOC:
        return "HEREDOC";
    case SIMPLE_CMD:
        return "SIMPLE_CMD";
    case BUILTIN_CMD:
        return "BUILTIN_CMD";
    case ARGUMENT:
        return "ARGUMENT";
    case FILE_EOF:
        return "FILE_EOF";
    default:
        return "UNKNOWN";
    }
}

void *free_and_return_null(void *ptr)
{
    free(ptr);
    return NULL;
}