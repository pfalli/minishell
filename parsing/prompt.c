/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:05:28 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 15:05:28 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// prompt->quotes = "\'\"";
void	init_prompt(t_prompt *prompt)
{
	memset(prompt, 0, sizeof(t_prompt));
	prompt->symbols = "<>";
	prompt->whitespace = "\t\r\v ";
}
