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

//	static void	sig_heredoc(int signal)
//	{
//		if (signal == SIGINT)
//			exit(130);
//	}

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

int	heredoc(char *end)
{
	int		fd;
	char	*line;

	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (printf("Error opening heredoc\n"), 0);
	while (1)
	{
		signal(SIGINT, sig_int_in_process);
		line = readline("heredoc> ");
		if (!line || (ft_strlen(line) == ft_strlen(end)
				&& ft_strncmp(line, end, ft_strlen(line)) == 0))
		{
			close(fd);
			open("/tmp/heredoc", O_RDONLY, 0644);
			unlink("/tmp/heredoc");
			return (free(line), fd);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (fd);
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
	{
		execve(cmdandfile->multi_command[0], cmdandfile->multi_command, data->envp);
		printf("'%s': command not found\n", cmdandfile->multi_command[0]);
		free_multi(cmdandfile->multi_command);
		exit(127);
	}
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
	return (close_and_original_fd(&exec), pid);
}

void	command_processor(t_token *cmdandfile, t_data *data)
{
	int	fds[2];
	int	prev_fd;
	int	original[2];
	int	last_pid;
	void		(*old_signal[2])(int);

	prev_fd = -1;
	original[0] = dup(0);
	original[1] = dup(1);
	set_signals(old_signal);
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
			last_pid = executor(cmdandfile, data, prev_fd, original[1]);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = fds[0];
		cmdandfile = cmdandfile->next;
	}
	wait_and_restore(original, last_pid, data);
	restore_signals(old_signal);
}
