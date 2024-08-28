/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:31:26 by atamas            #+#    #+#             */
/*   Updated: 2024/08/27 16:35:10 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_is_executable(char *joined_command)
{
	if (access(joined_command, X_OK) == 0)
		return (joined_command);
	else
		return (perror(joined_command), free(joined_command), NULL);
}

int	assign_and_close(int old_fd, int new_fd)
{
	if (new_fd > -1)
	{
		if (old_fd > 1)
			close(old_fd);
		return (new_fd);
	}
	return (old_fd);
}

void	create_original_fds(t_execution *exec)
{
	exec->in = 0;
	exec->out = 1;
	exec->o_stdin = dup(0);
	exec->o_stdout = dup(1);
}

void	close_and_original_fd(t_execution *exec)
{
	dup2(exec->o_stdout, 1);
	dup2(exec->o_stdin, 0);
	close(exec->o_stdout);
	close(exec->o_stdin);
	if (exec->out != 1)
		close(exec->out);
	if (exec->in != 0)
		close(exec->in);
}

void	wait_and_restore(int original[2], int last_pid, t_data *data)
{
	int	pid;
	int	status;

	status = -1;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
		}
		pid = wait(&status);
	}
	dup2(original[0], 0);
	dup2(original[1], 1);
	close(original[0]);
	close(original[1]);
}
