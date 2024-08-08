/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:35:40 by atamas            #+#    #+#             */
/*   Updated: 2023/11/25 23:49:01 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* 
Outputs the character 'c' to the given file descriptor
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int	main(void)
{
	char	test_char;
	int		test_fd;

	test_char = 'J';
	test_fd = 1;
	write(test_fd, "Before: ", 8);
	write(test_fd, &test_char, 1);
	write(test_fd, "\n", 1);
	ft_putchar_fd(test_char, test_fd);
	write(test_fd, "\n", 1);
} */
