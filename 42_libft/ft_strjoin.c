/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:24:03 by atamas            #+#    #+#             */
/*   Updated: 2023/11/16 19:04:46 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*start_of_string;
	char	*string;

	string = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!string)
		return (NULL);
	start_of_string = string;
	while (*s1 != '\0')
	{
		*string++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*string++ = *s2++;
	}
	*string = '\0';
	return (start_of_string);
}
