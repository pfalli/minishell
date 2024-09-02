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

int	g_sigint_exit_status = 0;

void	sig_int(int signal) // ctrl + C
{
	(void)signal;
	g_sigint_exit_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_int_in_process(int signal) // ctrl + C 
{
	(void)signal;
	g_sigint_exit_status = 130;
	printf("\n");
}

void	sig_quit(int signal) // ctrl + '\' QUit
{
	(void) signal;
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
