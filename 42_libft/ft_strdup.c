/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:23:18 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 20:16:51 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
/* #include <stdio.h> */

/* 
Allocates enough memory and then it does the copy
Return: pointer to the first char in the memory
	or NULL if the allocation failed
 */
char	*ft_strdup(const char *src)
{
	char	*memory;
	char	*start;
	int		len;

	len = 0;
	while (src[len] != '\0')
	{
		len++;
	}
	memory = malloc(sizeof(*src) * (len + 1));
	if (!memory)
		return (NULL);
	start = memory;
	while (*src)
	{
		*memory = *src;
		memory++;
		src++;
	}
	*memory = '\0';
	return (start);
}

/* int	main(void)
{
	char	*string;
	char	*result;

	string = "42 is the best school";
	result = ft_strdup(string);
	printf("The duplicated string is: %s\n", result);
	free(result);
}
 */