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

#include "../42_libft/libft.h"
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
    START = 0,
    REDIRECTION_IN,
    REDIRECTION_OUT,
    APPEND,
    HEREDOC,
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

typedef struct s_redirection
{
    char *file_name;
    t_type type;
    struct s_redirection *next;
}                                   t_redirection;


typedef struct s_token
{
    char *value;
    char **multi_command;
    char **multi_files;
    struct s_token *next;
    int cmd_count;
    int file_count;
    int word_count;
    t_redirection *redirection;
}									t_token;




// **************************************************************

void minishell_loop(t_prompt *prompt, t_token **token_list);

void parser(t_prompt *prompt);
t_token *lexing(t_prompt *prompt);
t_token *parsing(t_token *tokens, t_prompt *prompt);
void init_prompt(t_prompt *prompt);
t_token *create_linked_list(t_prompt *prompt, char *message);
t_token *create_token(char *word);
t_type search_type(char *word);
void append_node(t_token **head, t_token **current, t_token *new);

void print_token_details(t_token *token_list);
void print_redirection_list(t_redirection *redir_list);

// ** init ** //

t_token *init_multi_arrays(t_token *new, t_prompt *prompt);
bool initialize_multi_arrays(t_token *new, char *value_copy);

// ** utils ** //
int count_word(const char *str);
const char *type_to_string(enum s_type type);
void set_environment_variable(char *message);
void *free_and_return_null(void *ptr);

//** token.c **/
char *ft_strtok(char *str, const char *delim);
char *ft_strtok_copy(char *str, const char *delim);
size_t ft_strspn(const char *str, const char *accept);
bool is_quote(char c);
char *find_token_end(char *str, const char *delim);

// ** free ** //
void free_prompt(t_prompt *prompt);
void	ft_free_token_list(t_token *token_list);
void free_multi_arrays(t_token *token_list);
void	free_multi_arr(char **arr);
void free_readline();

// ** redirection**// 
t_redirection *create_redirection_list(t_token *new, t_prompt *prompt, char *word);
void append_redirection_node(t_redirection **head, t_redirection **current, t_redirection *new_node);
t_redirection *create_redirection_node(char *file_name, t_type type);

// ** dollar_sign **
char *extract_var_name(const char *str, int *index);
char *replace_var_with_value(const char *str, const char *var_value, int start, int var_len);
char *check_dollar_sign(char *command);
char *replace_variable(char *str, int *i);
char *expand_message(char *message);

#endif