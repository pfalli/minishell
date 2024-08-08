/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:42 by atamas            #+#    #+#             */
/*   Updated: 2023/12/02 15:00:57 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_num_multi_digits(int n)
{
	int	multidigit;

	multidigit = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		else
		{
			n *= -1;
			multidigit++;
		}
	}
	if (n == 0)
		multidigit++;
	while (n > 0)
	{
		multidigit++;
		n /= 10;
	}
	return (multidigit);
}

static int	handle_negative(char *string, int n)
{
	string[0] = '-';
	return (n * -1);
}

/* 
Makes integer to ascii
Input: integer
Return: the converted string
 */
char	*ft_itoa(int n)
{
	int		multidigit;
	int		i;
	int		until;
	char	*string;

	multidigit = ft_num_multi_digits(n);
	string = (char *)malloc(sizeof(char) * multidigit + 1);
	i = multidigit;
	until = i;
	if (!string)
		return (NULL);
	if (n == -2147483648)
		return (ft_memcpy(string, "-2147483648", 12));
	if (n < 0)
	{
		n = handle_negative(string, n);
		until -= 1;
	}
	while (0 < until--)
	{
		string[i-- - 1] = (n % 10) + '0';
		n /= 10;
	}
	string[multidigit] = '\0';
	return (string);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*string;
	int		yournumber;

	yournumber = -12;
	string = ft_itoa(-2147483648);
	printf("When the number is min int: %s\n", string);
	free(string);
	string = ft_itoa(2147483647);
	printf("When the number is max int: %s\n", string);
	free(string);
	string = ft_itoa(0);
	printf("When the number is zero: %s\n", string);
	free(string);
	string = ft_itoa(yournumber);
	printf("When the number is %d: %s\n", yournumber, string);
	free(string);
} */