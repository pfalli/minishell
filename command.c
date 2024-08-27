/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:53:46 by atamas            #+#    #+#             */
/*   Updated: 2024/08/24 20:43:16 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	command_on_path(char **executable, t_data *data)
{
	char	*command_with_slash;
	char	*joined_command;
	int		i;

	i = 0;
	if (!data->path || !data->path[0] || !executable || !executable[0])
		return (0);
	command_with_slash = ft_strjoin("/", executable[0]);
	while (data->path[i])
	{
		joined_command = ft_strjoin(data->path[i], command_with_slash);
		if (access(joined_command, F_OK) == 0)
		{
			free(command_with_slash);
			if (command_is_executable(joined_command))
				return (free(*executable), *executable = joined_command, 1);
			else
				return (-1);
		}
		free(joined_command);
		i++;
	}
	return (0);
}

void	wire_files(t_execution *exec, t_redirection *cmdandfile)
{
	t_redirection	*current;
	int				temp_in;
	int				temp_out;

	current = cmdandfile;
	temp_in = 0;
	temp_out = 1;
	while (current)
	{
		if (current->type == REDIRECTION_IN)
			temp_in = open(current->file_name, O_RDONLY, 0444);
		else if (current->type == REDIRECTION_OUT)
			temp_out = open(current->file_name, O_TRUNC | 01 | O_CREAT, 0644);
		else if (current->type == APPEND)
			temp_out = open(current->file_name, 01 | O_APPEND | O_CREAT, 0644);
		else if (current->type == HEREDOC)
			temp_in = printf("Heredoc needs to be called here");
		current = current->next;
		if (temp_in == -1 || temp_out == -1)
			perror("minishell");
		if (temp_in > -1)
			exec->in = assign_and_close(exec->in, temp_in);
		if (temp_out > -1)
			exec->out = assign_and_close(exec->out, temp_out);
	}
}

void	handle_input_output(t_execution *exec, int *in, int *out)
{
	if (exec->in != 0)
	{
		dup2(exec->in, 0);
		close(exec->in);
	}
	else if (*in != -1)
	{
		dup2(*in, 0);
		close(*in);
	}
	if (exec->out != 1)
	{
		dup2(exec->out, 1);
		close(exec->out);
	}
	else if (*out != 1)
	{
		dup2(*out, 1);
		close(*out);
	}
}

void	executor(t_token *cmdandfile, t_data *data, int in_fd, int out_fd)
{
	t_execution	exec;
	int			pid;
	void (*old_signal[2])(int);

	create_original_fds(&exec);
	wire_files(&exec, cmdandfile->redirection);
	handle_input_output(&exec, &in_fd, &out_fd);
	if (builtin(cmdandfile->multi_command, data) == 1)
		return (close_and_original_fd(&exec));
	if (access(cmdandfile->multi_command[0], X_OK) != 0)
		command_on_path(cmdandfile->multi_command, data);
	set_signals(old_signal);
	pid = fork();
	if (pid == -1)
		error("fork", NULL);
	else if (pid == 0)
	{
		execve(cmdandfile->multi_command[0], cmdandfile->multi_command, data->envp);
		printf("command not found: %s\n", cmdandfile->multi_command[0]);
		exit(1);
	}
	close_and_original_fd(&exec);
	restore_signals(old_signal);
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
}

void	command_processor(t_token *cmdandfile, t_data *data)
{
	int	fds[2];
	int	prev_fd;
	int	original[2];

	prev_fd = -1;
	original[0] = dup(0);
	original[1] = dup(1);
	while (cmdandfile)
	{
		if (cmdandfile->next)
		{
			if (pipe(fds) == -1)
				error("pipe", NULL);
			executor(cmdandfile, data, prev_fd, fds[1]);
			close(fds[1]);
		}
		else
			executor(cmdandfile, data, prev_fd, original[1]);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = fds[0];
		cmdandfile = cmdandfile->next;
	}
	wait_and_restore(original);
}
