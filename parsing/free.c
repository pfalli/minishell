/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/22 14:17:19 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/22 14:17:19 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token_list(t_token *token_list)
{
	t_token	*token_list_holder;

	if (!token_list)
		return ;
	while (token_list)
	{
		free(token_list->value);
		free_multi_arr(token_list->multi_command);
		//free_multi_arr(token_list->multi_files);
		token_list_holder = token_list;
		token_list = token_list->next;
		free(token_list_holder);
	}
}

void	free_prompt(t_prompt *prompt)
{
	free(prompt->symbols);
	free(prompt->whitespace);
}

void	free_multi_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_readline(void)
{
	rl_clear_history();
	rl_cleanup_after_signal();
	rl_deprep_terminal();
}
