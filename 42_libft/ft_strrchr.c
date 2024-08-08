/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:55:11 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 14:32:42 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *string, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = (char) c;
	while (string[i] != '\0')
	{
		i++;
	}
	if (ch == '\0')
		return ((char *)string + i);
	while (i >= 0)
	{
		if (string[i] == ch)
		{
			return ((char *)string + i);
		}
		i--;
	}
	return (0);
}
