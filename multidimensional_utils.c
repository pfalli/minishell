/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multidimensional_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:21:00 by atamas            #+#    #+#             */
/*   Updated: 2024/07/23 16:30:46 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_multi(char **multi)
{
	int	i;

	i = 0;
	while (multi[i])
	{
		printf("%s\n", multi[i++]);
	}
}

void	free_multi(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	multi_size(char **multidimensional)
{
	int	i;

	i = 0;
	if (multidimensional == NULL)
		return (0);
	while (multidimensional[i])
		i++;
	return (i);
}
