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

	if (!command[1] || ft_strncmp("~", command[1], 2) == 0)
	{
		free(command[1]);
		command[1] = value_finder("HOME=", env->envp);
		if (command[1] == NULL)
			return (printf("HOME is not set\n"), 1);
	}
	status = chdir(command[1]);
	if (status == -1)
		return (perror("cd"), 1);
	if (key_already_present("PWD=", env->envp, &pos))
		env->envp = add_to_multi(env->envp, "OLDPWD=", env->envp[pos] + 4);
	pwd = getcwd(NULL, 0);
	env->envp = add_to_multi(env->envp, "PWD=", pwd);
	free(pwd);
	return (1);
}

int	mini_echo(char **command)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	if (command[0] && ft_strncmp(command[0], "-n", 2) == 0)
	{
		new_line = 0;
		if (command[0][2] == '\0')
			i++;
		else
			command[0] += 2;
	}
	while (command[i + 1])
		printf("%s ", command[i++]);
	if (command[i])
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
	if (ft_strncmp(command[0], "pwd", 3) == 0)
	{
		pwd = getcwd(NULL, 0);
		return (printf("%s\n", pwd), free(pwd), 1);
	}
	if (ft_strncmp(command[0], "cd", 2) == 0)
		return (mini_cd(command, env));
	if (ft_strncmp(command[0], "export", 6) == 0)
		return (mini_export(command, env));
	if (ft_strncmp(command[0], "unset", 5) == 0)
		return (env->envp = mini_unset(command, env), 1);
	if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (mini_echo(command + 1));
	if (ft_strncmp(command[0], "env", 3) == 0)
		return (print_env(env->envp, 0));
	return (0);
}
