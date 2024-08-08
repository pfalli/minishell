/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:39:33 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 13:51:07 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/* #include <stdio.h>
#include <string.h> */

/* 
Copies len bytes from string src to string dst with handling overlap
Return: Original value of dst
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*destination;
	const char	*source;

	destination = (char *)dst;
	source = (const char *)src;
	if (!destination && !source)
		return (NULL);
	if (destination == source || len == 0)
		return (dst);
	if (destination > source)
	{
		while (len-- > 0)
			destination[len] = source[len];
	}
	else
	{
		while (len-- > 0)
			*destination++ = *source++;
	}
	return (dst);
}

/* int main() {
	char source1[] = "Hello, World!";
	char destination1[20];

	printf("Test case without overlapping memory:\n");
	ft_memmove(destination1, source1, strlen(source1) + 1);
	printf("Source: %s\n", source1);
	printf("Destination: %s\n", destination1);
	printf("\n");

	char source2[] = "Hello, World!";
	char destination2[20];

	printf("Test case with overlapping memory:\n");
	ft_memmove(destination2 + 7, source2, strlen(source2) + 1);
	printf("Source: %s\n", source2);
	printf("Destination: %s\n", destination2);
} */