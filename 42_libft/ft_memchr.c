/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:01:52 by atamas            #+#    #+#             */
/*   Updated: 2023/11/24 12:21:52 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/* #include <stdio.h> */

/* 
Locates the first occurence of the character c within n bytes
Input: pointer to the array
Return: pointer to the byte located or NULL if no such byte exists within n bytes
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*ptr == (unsigned char) c)
			return (ptr);
		ptr++;
		n--;
	}
	return (0);
}

/* int	main(void)
{
	const char	*string;
	int			search_char;
	int			length;
	char		*result;

	string = "Chasing dreams like a fox chasing fireflies in the twilight";
	search_char = 'x';
	length = 25;
	result = ft_memchr(string, search_char, length);
	if (result != NULL)
	{
		printf("Character '%c' found. \n", search_char);
		printf("Position is: %ld\n", (char *)result - string);
	}
	else
	{
		printf("'%c' was not in the first %d char.\n", search_char, length);
	}
}
 */