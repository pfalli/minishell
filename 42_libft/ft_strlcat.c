/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:10:45 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 18:17:21 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/* 
Appends string src to dst.
Return: is the length of dest if dstsize is 0 or the size 
of destination and scource added together
 */
int	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_length;
	size_t	src_length;
	size_t	i;
	size_t	j;

	if (!dst && !src)
		return (0);
	dest_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	i = dest_length;
	j = 0;
	if (dstsize < dest_length)
		return (dstsize + src_length);
	while (j + dest_length < dstsize && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if ((dest_length + j) == dstsize && j > 0)
		dst[i - 1] = '\0';
	else
		dst[i] = '\0';
	return (dest_length + src_length);
}

/* #include <stdio.h>
int	main(void)
{
	char dest[20] = "Andor ";
	char *from = "is happy";

	printf("The string is %s with nr: %d", dest, ft_strlcat(dest, from, 14));
} */