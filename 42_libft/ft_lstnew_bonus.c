/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:59:33 by atamas            #+#    #+#             */
/*   Updated: 2023/11/30 21:42:02 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/* #include <stdio.h>

int	main(void)
{
	int	i = 15;
	int j = 123;
	t_list	*test = ft_lstnew(&i);
	test->next = ft_lstnew(&j);
	printf("%p\n", &i);
	int *ptr = (int*)test->content;
	int *ptr2 = (int*)test->next->content;
	printf("%i\n", *ptr);
	printf("%i\n", *ptr2);
} */
