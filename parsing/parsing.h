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

#include "minishell.h"
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

typedef struct s_prompt
{
    char *message;
    char *symbols;
    char *off_symbols;
    char *quotes;
    char *whitespace;
    char *curr_dir;
    int word_count;
    
}                                   t_prompt

typedef struct s_token
{
	t_type	type;
    char *value;
	char **arr;
	struct s_token *next;
}									t_token;

typedef struct s_token_node                                          
{     
    t_token node;

    struct s_token_node *left;
    struct s_token_node *right;                      
}                                   t_token_node

typedef enum s_type
{
	END;
	ERROR;
	PIPE;
	REDIRECTION_IN;
    REDIRECTION_OUT;
	WORD;
	SIMPLE_CMD;
	BUILTIN_CMD;
    ARGUMENT;
    FILE_EOF;
}									t_type;


typedef struct s_binary_tree
{
    t_token_node *root;
}                                   t_binary_tree;


#endif