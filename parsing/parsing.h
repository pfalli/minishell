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


// ****TOKEN_LIST STRUCT****

typedef enum s_type
{
    WORD = 0,
    PIPE,
    REDIRECTION,
    SIMPLE_CMD, // command or argument
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
    char **multi_array_command;
    char **multi_array_files;
    struct s_token *next;
    struct s_token *prev;
    int cmd_count;
    int file_count;
    int word_count;
}									t_token;




// **************************************************************

void parser(t_prompt *prompt);
t_token *lexing(t_prompt *prompt);
t_token *parsing(t_token *tokens, t_prompt *prompt);
void init_prompt(t_prompt *prompt);
t_token *create_linked_list(t_prompt *prompt);
t_token *create_token(char *word);
t_type search_token_type(char *word);
void	ft_free_token_list(t_token *token_list);
void append_node(t_token **head, t_token **current, t_token *new);

t_token *init_multi_arrays(t_token *new, t_prompt *prompt);
bool initialize_multi_arrays(t_token *new, char *value_copy);
int count_word(const char *str);
char **ft_split(const char *str, char delimiter);
char *ft_strtok(char *str, const char *delim);
char *ft_strtok_copy(char *str, const char *delim);
size_t ft_strspn(const char *str, const char *accept);
size_t ft_strcspn(const char *str, const char *reject);
size_t ft_strlen_pipe(const char *str);

#endif