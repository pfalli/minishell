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
	int		status;
	int		pos;
	char	*pwd;
	char	*temp;

	if (!command[1] || ft_strncmp("~", command[1], 2) == 0)
	{
		temp = value_finder("HOME=", env->envp);
		if (temp == NULL)
			return (printf("HOME is not set\n"), 1);
	}
	else
		temp = command[1];
	status = chdir(temp);
	if (status == -1)
		return (perror("cd"), env->exit_status = 1, 1);
	if (key_already_present("PWD=", env->envp, &pos))
		env->envp = add_to_multi(env->envp, "OLDPWD=", env->envp[pos] + 4);
	pwd = getcwd(NULL, 0);
	env->envp = add_to_multi(env->envp, "PWD=", pwd);
	free(pwd);
	return (env->exit_status = 0, 1);
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

int	builtin(char **command, t_data *env)
{
	char	*pwd;

	if (!command || !command[0])
		return (-1);
	if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
	{
		if (command[1])
			return (printf("pwd: too many arguments\n"), 1);
		pwd = getcwd(NULL, 0);
		return (printf("%s\n", pwd), free(pwd), env->exit_status = 0, 1);
	}
	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
		return (mini_cd(command, env));
	if (ft_strncmp(command[0], "export", ft_strlen(command[0])) == 0)
		return (env->exit_status = 0, mini_export(command, env));
	if (ft_strncmp(command[0], "unset", ft_strlen(command[0])) == 0)
		return (env->exit_status = 0, env->envp = mini_unset(command, env), 1);
	if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (env->exit_status = 0, mini_echo(command));
	if (ft_strncmp(command[0], "env", ft_strlen(command[0])) == 0)
		return (env->exit_status = 0, print_env(env->envp, 0, command));
	if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		exit(0);
	return (0);
}
