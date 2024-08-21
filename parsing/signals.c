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

#include "../minishell.h"

volatile sig_atomic_t g_signal_received = 0; // if not global i create a struct for signals

void sig_int(int signal) // ctrl + C
{
    (void)signal;
    g_signal_received = SIGINT_RECEIVED;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sig_quit(int signal) // ctrl + '\'
{
    (void)signal;
    g_signal_received = SIGQUIT_RECEIVED;
    printf("Quit (core dumped)\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
