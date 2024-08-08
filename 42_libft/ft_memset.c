/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:35:26 by atamas            #+#    #+#             */
/*   Updated: 2023/11/24 14:48:20 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/* #include <stdio.h>
#include <string.h> */

/* 
Writes len bytes of value c (converted to an unsigned char) to the
	string b
Return: First argument
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) b;
	while (len != 0)
	{
		*ptr = (unsigned char) c;
		len--;
		ptr++;
	}
	return (b);
}

/* int main() {
	char str[20];
	char expected[20];
	int value;
	size_t len;

	value = 'A';
	len = 10;
	memset(expected, value, len);
	ft_memset(str, value, len);
	if (memcmp(str, expected, len) == 0) {
		printf("ft_memset is correct!\n");
	} else {
		printf("ft_memset is incorrect!\n");
	}
} */