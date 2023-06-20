#include "main.h"

#define BUFFER_SIZE 1024

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t bytes_read;

    while (1) {
        printf("simple_shell$ ");
        fflush(stdout);

        bytes_read = getline(&input, &input_size, stdin);

        if (bytes_read == -1) {
            printf("\n");
            break;  /* End of file (Ctrl+D) detected, exit the shell */
        }

        /* Remove the trailing newline character */
        if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
            input[bytes_read - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;  /* Exit the shell */
        } else if (strcmp(input, "env") == 0) {
            print_environment();
            continue;
        }

        execute_command(input);
    }

    free(input);
    return EXIT_SUCCESS;
}

