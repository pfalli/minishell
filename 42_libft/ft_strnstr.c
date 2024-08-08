/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:05:37 by atamas            #+#    #+#             */
/*   Updated: 2023/12/03 19:13:06 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big_str, const char *small_str, size_t len)
{
	size_t	small_len;

	if (*small_str == '\0')
		return ((char *)big_str);
	small_len = ft_strlen(small_str);
	while (*big_str && small_len <= len)
	{
		if (*big_str == *small_str)
		{
			if (!ft_strncmp((char *)big_str, (char *)small_str, small_len))
				return ((char *)big_str);
		}
		len--;
		big_str++;
	}
	return (0);
}

/* #include <stdio.h>

int	main(void)
{
	char	*bigstr;
	char	*retstr;

	bigstr = "Students lealma in the 42 school";
	// retstr = ft_strnstr(bigstr, "a", 12); test case fails it should not
	retstr = ft_strnstr(bigstr, "alma", 12);
	printf("String is: %s", retstr);
} */