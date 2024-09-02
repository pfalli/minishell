/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:45:32 by pfalli            #+#    #+#             */
/*   Updated: 2024/09/02 14:45:32 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_var_name(const char *str, int *index)
{
	char	var_name[256];
	int		j;

	j = 0;
	while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
		var_name[j++] = str[(*index)++];
	var_name[j++] = '=';
	var_name[j] = '\0';
	return (ft_strdup(var_name));
}

char	*replace_var_with_value(const char *str, const char *var_value,
		int start, int var_len)
{
	int		new_len;
	char	*new_str;

	new_len = ft_strlen(str) + ft_strlen(var_value) - var_len;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, start - var_len + 1);
	ft_strcat(new_str, var_value);
	ft_strcat(new_str, &str[start]);
	return (new_str);
}

char	*replace_with_exit_status(char *str, int *i, t_data *data)
{
	char	*var_value;
	char	*new_str;

	if (str[*i] == '?' && str[*i - 1] == '$')
	{
		var_value = ft_itoa(data->exit_status);
		if (!var_value)
			return (str);
		new_str = replace_var_with_value(str, var_value, *i + 1, 2);
		free(var_value);
		if (!new_str)
			return (str);
		free(str);
		return (new_str);
	}
	return (str);
}

char	*replace_variable(char *str, int *i, t_data *data)
{
	int		var_start;
	char	*var_name;
	char	*var_value;
	char	*new_str;

	var_start = *i;
	var_name = extract_var_name(str, i);
	if (!var_name)
		return (free_and_return_null(str));
	var_value = value_finder(var_name, data->envp);
	free(var_name);
	if (!var_value)
		return (str);
	new_str = replace_var_with_value(str, var_value, *i, *i - var_start);
	if (!new_str)
		return (free_and_return_null(str));
	free(str);
	return (new_str);
}

char	*check_dollar_sign(char *command, t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(command);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				str = replace_with_exit_status(str, &i, data);
			else
				str = replace_variable(str, &i, data);
			if (!str)
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}
