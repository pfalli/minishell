/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:10:34 by atamas            #+#    #+#             */
/*   Updated: 2023/11/24 12:35:25 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/* #include <stdio.h> */

/* 
The memcmp function compares byte string s1 against byte string s2.
Both strings are assumed to be n bytes long.
Return: 0 if both are identical, otherwise returns the difference between
	the first two differing bytes treated as unsigned char values
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*first_string;
	const unsigned char	*second_string;

	first_string = (const unsigned char *)s1;
	second_string = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*first_string != *second_string)
		{
			return (*first_string - *second_string);
		}
		first_string++;
		second_string++;
	}
	return (0);
}

/* int	main(void)
{
	const char	*string1;
	const char	*string2;
	int			compare_length;
	int			result;

	string1 = "Hello, World!";
	string2 = "Hello, Coder!";
	compare_length = 7;
	result = ft_memcmp(string1, string2, compare_length);
	if (result == 0)
	{
		printf("The first %d characters are identical.\n", compare_length);
	}
	else if (result < 0)
	{
		printf("String 1 is less than String 2.\n");
	}
	else
	{
		printf("String 1 is greater than String 2.\n");
	}
} */
