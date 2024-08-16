/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:50:33 by atamas            #+#    #+#             */
/*   Updated: 2024/07/26 20:51:02 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_shell_level(size_t level, char *old_level)
{
	char	*new_level;
	char	*level_with_key;
	int		len;

	if (level > 999)
		level = 1;
	new_level = ft_itoa(level);
	if (!new_level)
		return (printf("Allocation failed\n"), NULL);
	len = ft_strlen(new_level);
	level_with_key = malloc(sizeof(char) * (len + 7));
	if (!level_with_key)
		return (printf("Allocation failed\n"), free(new_level), NULL);
	ft_strlcpy(level_with_key, "SHLVL=", 7);
	ft_strlcpy(level_with_key + 6, new_level, len + 1);
	free(new_level);
	if (old_level)
		free(old_level);
	return (level_with_key);
}

int	set_default_env(t_data *env)
{
	char	*pwd;
	char	*level;

	pwd = getcwd(NULL, 0);
	env->envp = add_to_multi(env->envp, "PWD=", pwd);
	free(pwd);
	level = set_shell_level(1, NULL);
	env->envp = add_to_multi(env->envp, NULL, level);
	free(level);
	return (0);
}

int	init_path(t_data	*env)
{
	int	i;

	i = 0;
	env->path = NULL;
	if (env->envp == NULL)
		return (0);
	while (env->envp[i])
	{
		if (ft_strncmp("PATH=", env->envp[i], 5) == 0)
		{
			env->path = ft_split(env->envp[i] + 5, ':');
			if (env->path == NULL)
			{
				printf("Allocation failed\n");
				return (free_multi(env->envp), 1);
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int	init_env(char **envp, t_data *env)
{
	int	i;
	int	j;

	j = 0;
	env->envp = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (set_default_env(env), 0);
	i = multi_size(envp);
	env->envp = malloc(sizeof(char *) * (i + 1));
	if (env->envp == NULL)
		return (printf("Allocation failed\n"), 1);
	while (j < i)
	{
		env->envp[j] = ft_strdup(envp[j]);
		if (env->envp[j] == NULL)
			return (printf("Allocation failed\n"), free_multi(env->envp), 1);
		j++;
	}
	env->envp[i] = NULL;
	return (0);
}
