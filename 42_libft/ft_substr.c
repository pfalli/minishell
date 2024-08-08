/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:30:26 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 20:28:15 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	size_t			i;
	unsigned int	length_of_s;

	i = 0;
	if (!s)
		return (NULL);
	length_of_s = ft_strlen(s);
	if (len == 0 || start >= length_of_s)
		substring = malloc(sizeof(char) * 1);
	else if (len > length_of_s - start)
		substring = malloc((length_of_s - start + 1) * sizeof(char));
	else
		substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	while (i < len && start < length_of_s)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}

/* #include <stdio.h>

int	main(void)
{
	char	*string = "hola";
	char	*ret = ft_substr(string, 3, 2);
	printf("%s", ret);
} */