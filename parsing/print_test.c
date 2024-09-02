/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/08/21 14:15:30 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/21 14:15:30 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	void	print_token_details(t_token *token_list)
//	{
//		int			i;
//		int			j;
//		t_token		*current_token;
//	
//		i = 0;
//		current_token = token_list;
//		while (current_token != NULL)
//		{
//			printf("Token_value[%i]: %s\n", i, current_token->value);
//			if (current_token->multi_command == NULL)
//				printf("ERROR MULTI COMMAND\n");
//			printf("  Commands:\n");
//			j = 0;
//			while (j < current_token->cmd_count)
//			{
//				printf("    Command[%d]: %s\n", j,
//					current_token->multi_command[j]);
//				j++;
//			}
//			printf(" *** redirection_list***\n");
//			print_redirection_list(current_token->redirection);
//			current_token = current_token->next;
//			i++;
//		}
//	}

//	void	print_redirection_list(t_redirection *redir_list)
//	{
//		t_redirection	*current;
//	
//		current = redir_list;
//		while (current != NULL)
//		{
//			printf("    File_name: %s, Type: %s\n", current->file_name,
//				type_to_string(current->type));
//			current = current->next;
//		}
//	}

// only for testing print
//	const char	*type_to_string(t_type type)
//	{
//		switch (type)
//		{
//		case START:
//			return ("START");
//		case REDIRECTION_IN:
//			return ("REDIRECTION_IN");
//		case REDIRECTION_OUT:
//			return ("REDIRECTION_OUT");
//		case APPEND:
//			return ("APPEND");
//		case HEREDOC:
//			return ("HEREDOC");
//		case SIMPLE_CMD:
//			return ("SIMPLE_CMD");
//		case BUILTIN_CMD:
//			return ("BUILTIN_CMD");
//		case ARGUMENT:
//			return ("ARGUMENT");
//		case FILE_EOF:
//			return ("FILE_EOF");
//		default:
//			return ("UNKNOWN");
//		}
//	}
