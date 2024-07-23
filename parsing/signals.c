/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:31:22 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/22 09:31:22 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void sig_int (int signal)
{
    (void)signal;
    printf("\n");
}

void sig_quit(int signal)
{
    (void)signal;
    printf("Quit\n");
    kill();
}