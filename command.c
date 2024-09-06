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

int	command_on_path(char **executable, t_data *data)
{
	char	*command_with_slash;
	char	*joined_command;
	int		i;

	i = 0;
	if (!data->path || !data->path[0] || !executable || executable[0][0] == 0)
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
	return (free(command_with_slash), 0);
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
			temp_in = heredoc(current->file_name);
		current = current->next;
		if (temp_in == -1 || temp_out == -1)
			perror("minishell");
		if (temp_in > -1)
			exec->in = assign_and_close(exec->in, temp_in);
		if (temp_out > -1)
			exec->out = assign_and_close(exec->out, temp_out);
	}
}

int	executor(t_token *cmdandfile, t_data *data, int in_fd, int out_fd)
{
	t_execution	exec;
	int			pid;

	create_original_fds(&exec);
	wire_files(&exec, cmdandfile->redirection);
	handle_input_output(&exec, &in_fd, &out_fd);
	if (!cmdandfile->multi_command || !cmdandfile->multi_command[0])
		return (0);
	if (builtin(cmdandfile->multi_command, data, cmdandfile) == 1)
		return (close_and_original_fd(&exec), 0);
	if (access(cmdandfile->multi_command[0], X_OK) != 0)
		command_on_path(cmdandfile->multi_command, data);
	pid = fork();
	if (pid == -1)
		error("fork", NULL);
	else if (pid == 0)
		execute(cmdandfile, data);
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
	return (close_and_original_fd(&exec), pid);
}

int	command_processor(t_token *cmdandfile, t_data *data)
{
	int		fds[2];
	int		prev_fd;
	int		last_pid;
	void	(*old_signal[2])(int);

	prev_fd = -1;
	set_signals(old_signal);
	while (cmdandfile)
	{
		if (cmdandfile->next)
		{
			if (pipe(fds) == -1)
				error("pipe", NULL);
			executor(cmdandfile, data, prev_fd, fds[1]);
			close(fds[1]);
			prev_fd = fds[0];
		}
		else
			last_pid = executor(cmdandfile, data, prev_fd, 1);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = fds[0];
		cmdandfile = cmdandfile->next;
	}
	return (wait_and_restore(last_pid, data), restore_signals(old_signal), 0);
}
