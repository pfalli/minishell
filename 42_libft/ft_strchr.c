/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:30:31 by atamas            #+#    #+#             */
/*   Updated: 2023/11/28 14:28:52 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Locates the first occurence to character c in the string
Return: pointer to the character in the string or NULL
*/
char	*ft_strchr(const char *string, int c)
{
	char	ch;

	ch = (char)c;
	while (*string != '\0')
	{
		if (*string == ch)
		{
			return ((char *)string);
		}
		string++;
	}
	if (ch == '\0')
		return ((char *)string);
	return (0);
}
