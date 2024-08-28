/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:07:48 by atamas            #+#    #+#             */
/*   Updated: 2024/08/27 15:09:34 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *str, char *errormsg)
{
	if (!str)
		str = "minishell";
	if (!errormsg)
		perror(str);
	else
		printf("%s %s\n", str, errormsg);
	exit(1);
}