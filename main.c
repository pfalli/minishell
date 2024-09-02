/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@42student.wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:24:27 by atamas            #+#    #+#             */
/*   Updated: 2024/07/30 17:44:01 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_extractor(char *text)
{
	char	*key;
	int		start;
	int		end;
	int		i;

	start = -1;
	end = 0;
	i = 0;
	while (text[i] && end == 0)
	{
		if (text[i] == '$' && text[i + 1])
			start = ++i;
		if (start > -1 && (text[i + 1] == ' ' || text[i + 1] == '\n'
				|| text[i + 1] == '\0'))
			end = i + 1;
		i++;
	}
	key = malloc(sizeof(char) * (end - start + 1));
	if (key == NULL)
		return (printf("Allocation failed\n"), NULL);
	ft_strlcpy(key, text + start, (end - start + 1));
	return (key);
}

/* 
The value finder searches for the key if it finds a match than its 
	returns the pointer to the value
The key should be with the = sign if you searching through the environment
You should not free the returned value since its just pointing to the value
in the multidimensional array
 */
char	*value_finder(char *key, char **multidimensional)
{
	int	at_position;

	if (key_already_present(key, multidimensional, &at_position))
		return (multidimensional[at_position] + (ft_strlen(key)));
	else
		return (NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	env;
	t_prompt prompt;
    t_token *token_list = NULL;
	if (argc > 1 && argv[0] != NULL)
		return (printf("%s doesn't accept arguments!\n", argv[0]));
	if (init_env(envp, &env) || init_path(&env))
		return (0);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
    init_prompt(&prompt);
    minishell_loop(&prompt, &token_list, &env);
	free_multi(env.path);
	free_multi(env.envp);
	clear_history();
    free_readline();
	return (0);
}

