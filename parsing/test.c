/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:35:20 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/01 09:35:20 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while (1) {
        // Read a line of input from the user
        input = readline("Enter command: ");

        // Check if input is not NULL (user pressed Ctrl+D or input was empty)
        if (input == NULL) {
            printf("Goodbye!\n");
            break;
        }

        // Add input to history if it's not an empty string
        if (*input) {
            add_history(input);
        }

        // Process the input
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        printf("You entered: %s\n", input);

        // Free the memory allocated by readline
        free(input);
    }

    // Optional: Save history to a file or clear it before exiting
    clear_history();

    return 0;
}
