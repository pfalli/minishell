/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:16:27 by atamas            #+#    #+#             */
/*   Updated: 2023/11/25 23:27:29 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h> */

/* 
Applies the function 'f' on each character of the string passed as argument, 
	passing its index as first argument. Each character is passed by the address
		to 'f' to be modified if necessary
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/* void	toggle_case(unsigned int index, char *c)
{
	if (index > 1000)
		return ;
	if (*c >= 'a' && *c <= 'z') {
		*c = *c - 'a' + 'A';
	} else if (*c >= 'A' && *c <= 'Z') {
		*c = *c - 'A' + 'a';
	}
}

int	main()
{
	char str[] = "Hello, World!";

	printf("Original String: %s\n", str);
	ft_striteri(str, toggle_case);
	printf("Modified String: %s\n", str);
}
 */