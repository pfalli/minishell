/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:57:30 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/26 09:57:30 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

void	sig_heredoc(int signal)
{
	signal = 130;
	g_signal = signal;
	rl_redisplay();
	rl_done = 1;
	printf("\n");
}

void	sig_int(int signal) // ctrl + C
{
	signal = 130;
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void	sig_int_in_process(int signal) // ctrl + C 
{
	signal = 130;
	g_signal = signal;
	printf("\n");
}

void	sig_quit(int signal) // ctrl + '\' QUit
{
	signal = 131;
	g_signal = signal;
	printf("Quit\n");
}

void	set_signals(void (*old_signal[2])(int))
{
	old_signal[0] = signal(SIGINT, sig_int_in_process);
	old_signal[1] = signal(SIGQUIT, sig_quit);
}

void	restore_signals(void (*old_signal[2])(int))
{
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
}
