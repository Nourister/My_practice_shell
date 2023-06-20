#include "main.h"

#define BUFFER_SIZE 1024

char *custom_getline(void) {
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static ssize_t bytes_read = 0;

    if (position >= bytes_read) {
        position = 0;
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            return NULL;
        }
    }

    return &buffer[position++];
}

int main(void) {
    char *input = NULL;
    size_t input_length;

    while (1) {
        display_prompt();
        fflush(stdout);  /* Flush the output buffer */

        input = custom_getline();

        if (input == NULL) {
            printf("\n");
            break;  /* End of file (Ctrl+D) detected, exit the shell */
        }

        input_length = strlen(input); /* Move the assignment here */

        /* Remove the trailing newline character */
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;  /* Exit the shell */
        } else if (strcmp(input, "env") == 0) {
            print_environment();
            continue;
        }

        execute_command(input);
        free(input);
    }

    return EXIT_SUCCESS;
}

