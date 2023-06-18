#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

#define BUFFER_SIZE 1024

int main(void) {
    char input[BUFFER_SIZE];

    while (1) {
        printf("my_simple_shell$ ");
        fflush(stdout);

        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;  /* End of file (Ctrl+D) detected, exit the shell */
        }

        /* Remove the trailing newline character */
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;  /* Exit the shell */
        } else if (strcmp(input, "env") == 0) {
            print_environment();
            continue;
        }

        execute_command(input);
    }

    return EXIT_SUCCESS;
}

