/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:53:51 by atamas            #+#    #+#             */
/*   Updated: 2024/08/12 16:04:09 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(char **command, t_data *env)
{
	int		pos;
	char	*pwd;
	char	*temp;

	temp = command[1];
	if (!command[1] || ft_strncmp("~", command[1], 2) == 0)
	{
		temp = value_finder("HOME=", env->envp);
		if (temp == NULL)
			return (printf("HOME is not set\n"), 1);
	}
	else if (ft_strncmp(command[1], "-", 2) == 0)
	{
		temp = value_finder("OLDPWD=", env->envp);
		if (temp == NULL)
			return (printf("minishell: cd: OLDPWD not set\n"), 1);
	}
	if (chdir(temp) == -1)
		return (perror("cd"), env->exit_status = 1, 1);
	if (key_already_present("PWD=", env->envp, &pos))
		env->envp = add_to_multi(env->envp, "OLDPWD=", env->envp[pos] + 4);
	pwd = getcwd(NULL, 0);
	env->envp = add_to_multi(env->envp, "PWD=", pwd);
	return (free(pwd), env->exit_status = 0, 1);
}

int	echo_first_line(char *command, int space)
{
	int	new_line;
	int	i;

	i = 0;
	new_line = 1;
	if (!command)
		return (new_line);
	if (ft_strlen(command) >= 2 && ft_strncmp(command, "-n", 2) == 0)
	{
		i = 2;
		while (command[i] && command[i] == 'n')
			i++;
		if (command[i] != '\0' || command[i] != ' ')
			new_line = 0;
		else
			i = 0;
	}
	if (space && new_line == 1)
		printf("%s ", command + i);
	else
		printf("%s", command + i);
	return (new_line);
}

int	mini_echo(char **command)
{
	int		new_line;
	int		i;
	int		space;

	space = 0;
	if (command[1] && command[2])
		space = 1;
	new_line = echo_first_line(command[1], space);
	i = 2;
	while (command[1] && command[i] && command[i + 1])
		printf("%s ", command[i++]);
	if (command[1] && command[i])
		printf("%s", command[i]);
	if (new_line)
		printf("\n");
	return (1);
}

void	mini_exit(char *exit_arg, t_data *env, t_token *all, int loopflag)
{
	int	exit_num;

	printf("exit\n");
	free_multi(env->envp);
	free_multi(env->path);
	if (exit_arg)
		exit_num = ft_atoi(exit_arg) % 256;
	else
		exit_num = env->exit_status;
	clear_history();
	free_readline();
	if (!loopflag)
		ft_free_token_list(all);
	exit(exit_num);
}

int	builtin(char **command, t_data *env, t_token *all)
{
	char	*pwd;

	if (!command || !command[0])
		return (-1);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
	{
		if (command[1])
			return (printf("pwd: too many arguments\n"), 1);
		pwd = getcwd(NULL, 0);
		return (printf("%s\n", pwd), free(pwd), env->exit_status = 0, 1);
	}
	if (ft_strncmp(command[0], "cd", 3) == 0)
		return (mini_cd(command, env));
	if (ft_strncmp(command[0], "export", 7) == 0)
		return (env->exit_status = 0, mini_export(command, env));
	if (ft_strncmp(command[0], "unset", 6) == 0)
		return (env->exit_status = 0, env->envp = mini_unset(command, env), 1);
	if (ft_strncmp(command[0], "echo", 5) == 0)
		return (env->exit_status = 0, mini_echo(command));
	if (ft_strncmp(command[0], "env", 4) == 0)
		return (env->exit_status = 0, print_env(env->envp, 0, command, 0));
	if (ft_strncmp(command[0], "exit", 5) == 0)
		mini_exit(command[1], env, all, 0);
	return (0);
}
