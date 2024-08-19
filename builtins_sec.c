/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_sec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:58:50 by atamas            #+#    #+#             */
/*   Updated: 2024/08/19 16:03:07 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (1);
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

char	**mini_unset(char **command, t_data *env)
{
	if (command[1] == NULL)
		return (printf("unset: not enough arguments\n"), NULL);
	if (ft_strncmp("PATH", command[1], ft_strlen(command[1])) == 0)
	{
		free_multi(env->path);
		env->path = NULL;
	}
	return (remove_from_multi(env->envp, command[1]));
}

int	print_env(char **multidimensional, int sort)
{
	char	**sorted;
	int		size;
	int		i;

	i = 0;
	size = multi_size(multidimensional);
	if (size < 0)
		return (1);
	if (sort == 1)
	{
		sorted = malloc(sizeof(char *) * (size + 1));
		if (sorted == NULL)
			return (printf("Allocation failed\n"), 1);
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
