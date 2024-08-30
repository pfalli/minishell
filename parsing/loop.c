/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:02:42 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 14:44:27 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*check_syntax(char *word)
{
	char	*new;
	size_t	len;

	len = ft_strlen(word);
	if (!word || (len < 2))
		return (NULL);
	new = (char *)malloc(len - 1);
	if (!new)
		return (NULL);
	strncpy(new, word + 1, len - 2);
	new[len - 2] = '\0';
	return (ft_strdup(new));
}

void update_exit_status(t_data *data)
{
    if (g_sigint_exit_status != 0)
    {
        data->exit_status = g_sigint_exit_status;
        g_sigint_exit_status = 0;
    }
}

void	minishell_loop(t_prompt *prompt, t_token **token_list, t_data *data)
{
	char	*message;

	while (1)
	{
		message = readline(RED "MINISHELL$$ " RESET);
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		update_exit_status(data);
		if (message == NULL)
			mini_exit(NULL, data);
		else
			add_history(message);
		message = expand_message(message, data);
		message = redirection_with_no_space(message);
		*token_list = create_linked_list(prompt, message);
		//print_token_details(*token_list);
		command_processor(*token_list, data);
		if (message)
			free(message);
		ft_free_token_list(*token_list);
	}
}
