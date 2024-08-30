/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:29:22 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 14:29:22 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define RED "\x1b[31m"
# define RESET "\x1b[0m"

# include "../42_libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# include <wait.h>

typedef struct s_token	t_token;
typedef struct s_data	t_data;

# define SIGINT_RECEIVED 1
# define SIGQUIT_RECEIVED 2

//****TOKEN_LIST STRUCT****

typedef enum e_type
{
	START = 0,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	APPEND,
	HEREDOC,
	SIMPLE_CMD,
	BUILTIN_CMD,
	ARGUMENT,
	FILE_EOF
}	t_type;

typedef struct s_prompt
{
	char	*symbols;
	char	*whitespace;
}				t_prompt;

typedef struct s_redirection
{
	char					*file_name;
	t_type					type;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_token
{
	char			*value;
	char			**multi_command;
	char			**multi_files;
	struct s_token	*next;
	int				cmd_count;
	int				file_count;
	int				word_count;
	t_redirection	*redirection;
}				t_token;

// **************************************************************

void	minishell_loop(t_prompt *prompt, t_token **token_list, t_data *data);

void	init_prompt(t_prompt *prompt);
t_token	*create_linked_list(t_prompt *prompt, char *message);
t_token	*create_token(char *word);
t_type	search_type(char *word);
void	append_node(t_token **head, t_token **current, t_token *new);

// ** init ** //

t_token	*init_multi_command(t_token *new, t_prompt *prompt);
bool	initialize_multi_arrays(t_token *new, char *value_copy);

// ** utils ** //
int			count_word(const char *str);
const char	*type_to_string(t_type type);
void		set_environment_variable(char *message);
void		*free_and_return_null(void *ptr);
char		*ft_strcat(char *dest, const char *src);
void		print_token_details(t_token *token_list);
void		print_redirection_list(t_redirection *redir_list);
char		*remove_dollar(char *str);

//** token.c**/
char	*ft_strtok(char *str, const char *delim);
char	*ft_strtok_copy(char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *accept);
bool	is_quote(char c);
char	*string_with_quotes(char *str, const char *delim);
char	*check_syntax(char *word);

// ** free ** //
void	free_prompt(t_prompt *prompt);
void	ft_free_token_list(t_token *token_list);
void	free_multi_arrays(t_token *token_list);
void	free_multi_arr(char **arr);
void	free_readline(void);
void	free_redirection_node_list(t_redirection *redirection);

// ** redirection**//
t_redirection	*create_redirection_list(t_token *new, t_prompt *prompt,
	char *word);
void			append_redirection_node(t_redirection **head,
	t_redirection **current, t_redirection *new_node);
t_redirection	*create_redirection_node(char *file_name, t_type type);
bool is_redirection_operator(const char *word);

// ** dollar_sign **//
char	*extract_var_name(const char *str, int *index);
char	*replace_var_with_value(const char *str, const char *var_value,
		int start, int var_len);
char	*check_dollar_sign(char *command, t_data *data);
char	*replace_variable(char *str, int *i, t_data *data);
char	*expand_message(char *message, t_data *data);
char	*get_env_value(const char *var_name, t_data *env);
bool	single_quote(const char *str);

int if_only_spaces(const char *str);
void init_list_nodes(t_token **head, t_token **current, t_token **new);

// ** signals ** //
void	sig_int(int signal);
void	sig_quit(int signal);
void	sig_int_in_process(int signal);
void	set_signals(void (*old_signal[2])(int));
void	restore_signals(void (*old_signal[2])(int));

// ***redirection_no_spaces*** //
bool is_redirection_symbol(char c);
char *redirection_with_no_space(char *message);
bool is_redirection_operator(const char *word);

#endif