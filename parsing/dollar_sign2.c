/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:53:11 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 13:55:15 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_message(char *message, t_data *data)
{
	char	*expanded_message;
	char	*removed;

	if (single_quote(message))
		return (message);
	expanded_message = check_dollar_sign(message, data);
	if (expanded_message)
	{
		free(message);
		message = expanded_message;
	}
	removed = remove_dollar(message);
	return (removed);
}
