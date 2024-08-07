/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:17:19 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/22 14:17:19 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_token_list(t_token *token_list)
{
	t_token	*token_list_holder;

	if (!token_list)
		return ;
	while (token_list)
	{
		free(token_list->value);
        free_multi_arr(token_list->multi_command);
        free_multi_arr(token_list->multi_files);
		token_list_holder = token_list;
		token_list = token_list->next;
		free(token_list_holder);
	}
}

void free_prompt(t_prompt *prompt)
{
    if (prompt->message)
	{
        free(prompt->message);
        prompt->message = NULL; // Avoid double free
    }
    //free(prompt->symbols);
    //free(prompt->off_symbols);
    //free(prompt->quotes);
    //free(prompt->whitespace);
    if (prompt->curr_dir)
	{
        free(prompt->curr_dir);
        prompt->curr_dir = NULL;
    }
    if (prompt->ptr_prompt)
	{
        free(prompt->ptr_prompt);
        prompt->ptr_prompt = NULL;
    }
    //	if (prompt->multi_array) {
    //	    for (int i = 0; prompt->multi_array[i] != NULL; i++) {
    //	        free(prompt->multi_array[i]);
    //	    }
    //	    free(prompt->multi_array);
    //	}
}


void	free_multi_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void free_readline()
{
    rl_clear_history();
    rl_cleanup_after_signal();
    rl_deprep_terminal();
}
