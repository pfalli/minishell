/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:29:50 by atamas            #+#    #+#             */
/*   Updated: 2023/11/24 13:05:07 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h> */
#include <stddef.h>

/* 
Copies n bytes from memory area src to memory area dst until n
Return: The original value of dst
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_iterator;
	const unsigned char	*src_iterator;

	if (!dst && !src)
		return (NULL);
	dst_iterator = (unsigned char *) dst;
	src_iterator = (const unsigned char *) src;
	while (n > 0)
	{
		*dst_iterator = *src_iterator;
		dst_iterator++;
		src_iterator++;
		n--;
	}
	return (dst);
}

/* int main()
{
	char str2[] = "bonjour  a";
	char str1[13];
	str1[12] = '\0';
	int len = 7;
	ft_memcpy(str1, str2, len);
	printf("Copied string is: %s\n", str1);
} */
