/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:41:13 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 15:34:12 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

/* 
Allocates and sets the memory to null
Input: the amount of memory called count and the size is the sizeof the memory
Return: pointer to the start of memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*start_of_memory;

	start_of_memory = malloc(count * size);
	if (!start_of_memory)
		return (NULL);
	ft_bzero(start_of_memory, count * size);
	return (start_of_memory);
}

/* #include <stdio.h>

int	main(void)
{
	char	*test = ft_calloc(3, sizeof(char));
	test[0] = 'a';
	printf("%s\n", test);
}
 */