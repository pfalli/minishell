/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:55:27 by atamas            #+#    #+#             */
/*   Updated: 2023/11/27 09:00:45 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/* 
Outputs the string 's' to the given file descriptor with a newline at the end
 */
void	ft_putendl_fd(char *s, int fd)
{
	int	length;

	length = ft_strlen(s);
	write(fd, s, length);
	write(fd, "\n", 1);
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
	ft_putendl_fd(test_string, test_fd);
	write(test_fd, "\n", 1);
} */