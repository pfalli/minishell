#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "Hello, World! Welcome to C programming.";
    const char delimiters[] = " ,!."; // Delimiters are space, comma, exclamation, and period

    char *token = strtok(str, delimiters); // Get the first token

    while (token != NULL)
    {
        printf("%s\n", token); // Print each token
        token = strtok(NULL, delimiters); // Get the next token
    }
    return 0;
}