/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:02:06 by atamas            #+#    #+#             */
/*   Updated: 2024/09/06 11:03:25 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_token *cmdandfile, t_data *data)
{
	char	**multi;

	multi = cmdandfile->multi_command;
	execve(multi[0], multi, data->envp);
	printf("'%s': command not found\n", multi[0]);
	ft_free_token_list(cmdandfile);
	exit(127);
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
		signal(SIGINT, sig_heredoc);
		line = readline("> ");
		if (!line || (ft_strlen(line) == ft_strlen(end)
				&& ft_strncmp(line, end, ft_strlen(line)) == 0)
			|| g_signal == 130)
		{
			close(fd);
			fd = open("/tmp/heredoc", O_RDONLY, 0644);
			unlink("/tmp/heredoc");
			return (free(line), fd);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (fd);
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
