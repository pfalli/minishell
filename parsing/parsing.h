/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:02:00 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/15 12:02:00 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> // open
#include <wait.h> // wait, waitpid
#include <sys/stat.h>
#include <signal.h> // signal, kill
#include <errno.h> // errno
#include <term.h> // termcap
#include <dirent.h> // opendir
#include <string.h> // strerror
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


// ****LEXING STRUCTURE****

typedef enum s_type
{
    END,
    ERROR,
    PIPE,
    REDIRECTION,
    WORD, // command or argument
    SIMPLE_CMD,
    BUILTIN_CMD,
    ARGUMENT,
    FILE_EOF
}									t_type;

typedef struct s_prompt
{
    char *message;
    char *symbols;
    char *off_symbols;
    char *quotes;
    char *whitespace;
    char *curr_dir;
    int word_count;
    char *ptr_prompt;
    char **multi_array;
    
}                                   t_prompt;

typedef struct s_token
{
	t_type	type;
    char *value;
    struct s_token *next;
    struct s_token *prev;
    int token_count;
}									t_token;


// **************************************************************

void parser(t_prompt *prompt);
t_token *lexing(t_prompt *prompt);
t_token *parsing(t_token *tokens, t_prompt *prompt);
void init_prompt(t_prompt *prompt);
t_token *create_linked_list(t_prompt *prompt);
t_token *create_token(char *word);
t_token init_token(char *word);
t_type search_token_type(char *word);
void add_node_to_list(t_token **head, t_token **current, t_token *new_node);
t_token init_word(t_prompt *prompt);
char *ft_strtok(char *str, const char *delim);
void	ft_free_token_list(t_token *token_list);

#endif