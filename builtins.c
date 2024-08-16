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

	if (ft_strncmp("~", command[1], 2) == 0)
	{
		free(command[1]);
		command[1] = value_finder("HOME=", env->envp);
		if (command[1] == NULL)
			return (printf("HOME is not set\n"), -1);
	}
	status = chdir(command[1]);
	if (status == -1)
		return (perror("cd"), -1);
	if (key_already_present("PWD=", env->envp, &pos))
		env->envp = add_to_multi(env->envp, "OLDPWD=", env->envp[pos]);
	pwd = getcwd(NULL, 0);
	env->envp = add_to_multi(env->envp, "PWD=", pwd);
	free(pwd);
	return (1);
}

void	bubblesort(char **array, int n)
{
	int		i;
	int		j;
	int		sorted;
	char	*temp;

	i = 0;
	j = 0;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strncmp(array[j], array[j + 1], 10) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				sorted = 0;
			}
			j++;
		}
		i++;
	}
}

int	print_env(char **multidimensional, int sort)
{
	char	**sorted;
	int		size;
	int		i;

	i = 0;
	if (sort == 1)
	{
		size = multi_size(multidimensional);
		sorted = malloc(sizeof(char *) * (size + 1));
		if (sorted == NULL)
			return (printf("Allocation failed\n"), -1);
		sorted[0] = NULL;
		copy_multi_from(multidimensional, sorted, 0, size + 1);
		bubblesort(sorted, size);
		while (sorted[i] && sorted[i + 1])
			printf("declare -x %s\n", sorted[i++]);
		return (free(sorted), 1);
	}
	while (multidimensional[i])
	{
		if (ft_strchr(multidimensional[i], '='))
			printf("%s\n", multidimensional[i]);
		i++;
	}
	return (1);
}

char	*export_key(char *src)
{
	char	*key;
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	if (src[i] != '=' || i == 0)
		return (NULL);
	key = malloc(sizeof(char) * (i + 2));
	ft_strlcpy(key, src, i + 2);
	return (key);
}

int	mini_export(char **command, t_data *env)
{
	char	*key;
	char	*value;

	if (command[1] == NULL)
		return (print_env(env->envp, 1), 1);
	key = export_key(command[1]);
	if (key == NULL)
		return (-1);
	value = command[1] + ft_strlen(key);
	env->envp = add_to_multi(env->envp, key, value);
	if (ft_strncmp("PATH=", key, ft_strlen(key)) == 0)
	{
		free_multi(env->path);
		env->path = ft_split(value, ':');
	}
	free(key);
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
	while (command[i])
		printf("%s", command[i++]);
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
	{
		if (ft_strncmp("PATH", command[1], ft_strlen(command[1])) == 0)
			free_multi(env->path);
		env->path = NULL;
		return (env->envp = remove_from_multi(env->envp, command[1]), 1);
	}
	if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (mini_echo(command + 1));
	if (ft_strncmp(command[0], "env", 3) == 0)
		return (print_env(env->envp, 0));
	return (0);
}
