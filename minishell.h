/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:42:02 by atamas            #+#    #+#             */
/*   Updated: 2024/08/12 16:21:34 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "parsing/parsing.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "42_libft/libft.h"

typedef struct s_data
{
	char	**envp;
	char	**path;
}	t_data;

typedef struct s_execution
{
	int	in;
	int	out;
	char **cmd;
}	t_execution;

void	free_multi(char **array);
int		multi_size(char **multidimensional);
char	**add_to_multi(char **multi_dimensional, char *key, char *value);
char	**copy_multi_from(char **src, char **dest, int start, int size);
char	**remove_from_multi(char **multi_dimensional, char *key);
char	*update_key(char *key, char *new_value);
int		key_already_present(char *key, char **array, int *at_position);
void	print_multi(char **multi);
char	*set_shell_level(size_t level, char *old_level);
int		set_default_env(t_data *env);
int		init_path(t_data	*env);
int		init_env(char **envp, t_data *env);
int		builtin(char **command, t_data *env);
int		mini_export(char **command, t_data *env);
char	**mini_unset(char **command, t_data *env);
int	print_env(char **multidimensional, int sort);
char	*key_extractor(char *text);
char	*value_finder(char *key, char **multidimensional);
char	*export_key(char *src);
int		command_on_path(char **executable, t_data *data);
void	command_processor(t_token *cmdandfile, t_data *data);
#endif