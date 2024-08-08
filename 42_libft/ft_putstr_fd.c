/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:57:20 by atamas            #+#    #+#             */
/*   Updated: 2023/11/27 07:48:14 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/* 
Outputs the string 's' to the given file descriptor
 */
void	ft_putstr_fd(char *s, int fd)
{
	int	length;

	length = ft_strlen(s);
	write(fd, s, length);
}

/* int	main(void)
{
	char	*test_string;
	int		test_fd;

	test_string = "The string is stringing";
	test_fd = 1;
	write(test_fd, "Before: ", 8);
	write(test_fd, test_string, 24);
	write(test_fd, "\n", 1);
	ft_putstr_fd(test_string, test_fd);
	write(test_fd, "\n", 1);
} */