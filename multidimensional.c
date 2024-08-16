/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multidimensional.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@42student.wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:16:22 by atamas            #+#    #+#             */
/*   Updated: 2024/07/25 20:38:50 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_to_multi(char **multi_dimensional, char *key, char *value)
{
	int		i;
	int		j;
	int		at_position;
	char	**new_multi;

	at_position = 0;
	if (key_already_present(key, multi_dimensional, &at_position))
	{
		free(multi_dimensional[at_position]);
		multi_dimensional[at_position] = update_key(key, value);
		return (multi_dimensional);
	}
	i = multi_size(multi_dimensional);
	new_multi = malloc(sizeof(char *) * (i + 2));
	if (new_multi == NULL)
		return (printf("Allocation failed\n"), NULL);
	j = 0;
	while (j < i)
	{
		new_multi[j] = multi_dimensional[j];
		j++;
	}
	new_multi[j++] = update_key(key, value);
	new_multi[j] = NULL;
	return (free(multi_dimensional), new_multi);
}

int	key_already_present(char *key, char **multi_dimensional, int *at_position)
{
	int	i;
	int	key_len;

	i = 0;
	if (!key || !multi_dimensional || !multi_dimensional[0])
		return (0);
	key_len = ft_strlen(key);
	while (multi_dimensional[i])
	{
		if (ft_strncmp(key, multi_dimensional[i], key_len) == 0)
			return (*at_position = i, 1);
		i++;
	}
	return (0);
}

char	*update_key(char *key, char *new_value)
{
	int		key_len;
	int		value_len;
	char	*updated;

	key_len = 0;
	value_len = 0;
	if (key)
		key_len = ft_strlen(key);
	if (new_value)
		value_len = ft_strlen(new_value);
	updated = malloc(key_len + value_len + 1);
	if (updated == NULL)
		return (printf("Allocation failed\n"), NULL);
	if (key)
		ft_strlcpy(updated, key, key_len + 1);
	if (new_value)
		ft_strlcpy(updated + key_len, new_value, value_len + 1);
	return (updated);
}

char	**remove_from_multi(char **multi_dimensional, char *key)
{
	int		size;
	int		at_position;
	char	**new_multi;

	at_position = 0;
	if (!key_already_present(key, multi_dimensional, &at_position))
		return (multi_dimensional);
	size = multi_size(multi_dimensional);
	new_multi = malloc(sizeof(char *) * size);
	if (new_multi == NULL)
		return (printf("Allocation failed\n"), NULL);
	new_multi[0] = NULL;
	new_multi = copy_multi_from(multi_dimensional, new_multi, 0, at_position);
	new_multi = copy_multi_from(multi_dimensional, new_multi,
			at_position + 1, size);
	free(multi_dimensional[at_position]);
	free(multi_dimensional);
	return (new_multi);
}

char	**copy_multi_from(char **src, char **dest, int start, int size)
{
	int	i;
	int	j;

	i = start;
	j = multi_size(dest);
	while (i < size && src[i])
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = NULL;
	return (dest);
}
