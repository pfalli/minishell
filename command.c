/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:53:46 by atamas            #+#    #+#             */
/*   Updated: 2024/08/12 16:44:18 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*command_is_executable(char *joined_command)
{
	if (access(joined_command, X_OK) == 0)
		return (joined_command);
	else
		return (perror(joined_command), free(joined_command), NULL);
}

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

void	executor(t_token *cmdandfile, t_data *data)
{
	t_execution	exec;
	int			pid;
	int			status;
	void (*old_signal[2])(int);

	create_original_fds(&exec);
	wire_files(&exec, cmdandfile->redirection);
	dup2(exec.out, 1);
	dup2(exec.in, 0);
	if (builtin(cmdandfile->multi_command, data) == 1)
		return (close_and_original_fd(&exec));
	if (access(cmdandfile->multi_command[0], X_OK) != 0)
		command_on_path(cmdandfile->multi_command, data);
	set_signals(old_signal);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		execve(cmdandfile->multi_command[0], cmdandfile->multi_command, data->envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close_and_original_fd(&exec);
	restore_signals(old_signal);
	return ;
}

void	command_processor(t_token *cmdandfile, t_data *data)
{
	while (cmdandfile)
	{
		executor(cmdandfile, data);
		cmdandfile = cmdandfile->next;
	}
}
