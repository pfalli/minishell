/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:45:45 by pfalli            #+#    #+#             */
/*   Updated: 2024/07/04 14:45:45 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void show_prompt(void)
{
    printf(RED"MINISHELL$$ "RESET);
}

char **set_env(char **envp) // manipulate environment
{
    envp[0] = "PATH=/bin";
    return envp;
}

char *ft_strtok(char *str, const char *delim)
{

}

int main(int argc, char *argv[], char *envp[])
{
    char command[1024];
    int prompt_flag = 0;
    while (1)
    {
        show_prompt();
        while (fgets(command, sizeof(command), stdin) != NULL) 
        {
            command[strcspn(command, "\n")] = 0; // Remove newline character

            // Tokenize
            char *tokens[256];
            int i = 0;
            tokens[i] = strtok(command, " ");
            while (tokens[i] != NULL)
            {
                tokens[++i] = strtok(NULL, " ");
            }
            if (tokens[0] != NULL) // Ensure there's at least one token
            {
                if (strcmp(tokens[0], "ls") == 0)
                {
                    pid_t pid = fork();

                    if (pid == 0)  // Child process
                    {
                        char *args[] = {"/bin/ls", NULL}; // Arguments for execve
                        char **envp_modified = set_env(envp); // Modify env variables
                        if (execve(args[0], args, envp_modified) == -1) 
                        {
                            perror("execve");
                            exit(EXIT_FAILURE);
                        }
                    } else if (pid > 0) // Parent process
                    {
                        int status;
                        waitpid(pid, &status, 0); // Wait for child process
                    }
                    else // Fork failed
                        perror("fork");
                } 
                else 
                    printf("Command not recognized: %s\n", tokens[0]);
            }
        }
    }
    return 0;
}