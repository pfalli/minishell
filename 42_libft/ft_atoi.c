/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:16:55 by atamas            #+#    #+#             */
/*   Updated: 2023/11/23 16:31:50 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Makes ascii to integer until it reaches the first character
	that not integer
Input: string
Return: integer that got converted from ascii
 */
int	ft_atoi(const char *str)
{
	int	minus;
	int	integer;

	minus = 1;
	integer = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\n' || *str == '\v' || *str == '\f')
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		integer = integer * 10 + (*str - '0');
		str++;
	}
	return (integer * minus);
}

/* #include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*string;
	int		my_atoi;

	string = "-2147483648";
	my_atoi = 0;
	my_atoi = ft_atoi(string);
	printf("The ft_atoi return value is: %d\n", my_atoi);
	printf("The original atoi return is: %d\n", atoi(string));
} */