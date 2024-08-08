/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:38:38 by atamas            #+#    #+#             */
/*   Updated: 2023/11/23 16:33:01 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* 
Fills the given memory buffer with nulls until n
Input: pointer to void *s and integer n
Return: Nothing
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		*ptr++ = 0;
		n--;
	}
}

/* #include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char string[] = "Give me a test string";
	ft_bzero(string, 2);
	string[0] = 'a';
	printf("String is: %s\n", string);
} */