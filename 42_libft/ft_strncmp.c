/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:16:07 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 18:37:31 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(char *s1, char *s2, size_t until)
{
	while ((*s1 != '\0' || *s2 != '\0') && until > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		until--;
	}
	return (0);
}

/* #include <stdio.h>

int	main(void)
{
	char	*first = "Andor is home";
	char	*second = "Andor is here";
	printf("The diff is: %d", ft_strncmp(first, second, 12));
} */