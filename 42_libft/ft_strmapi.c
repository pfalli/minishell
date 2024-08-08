/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:58:05 by atamas            #+#    #+#             */
/*   Updated: 2023/11/25 18:00:45 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* 
Applies the function 'f'(index, char) to each character of the string 's'
Return: string created from the successive applications of 'f'
	or NULL if the allocations fails
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*memory;

	i = 0;
	memory = malloc(ft_strlen(s) + 1);
	if (!memory)
		return (NULL);
	while (s[i] != '\0')
	{
		memory[i] = f(i, s[i]);
		i++;
	}
	memory[i] = '\0';
	return (memory);
}

/* char map_function(unsigned int index, char c)
{
	int	i = index;
	if (i == 100)
		return (0);
	return (c + 1);
}

#include <stdio.h>
int	main(void)
{
	char	*string = "Rbgnnk";
	char	*res = ft_strmapi(string, &map_function);
	printf("%s\n", res);
	free(res);
} */