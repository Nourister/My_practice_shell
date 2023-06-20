#include "main.h"

int main(void) {
    char *input = NULL;
    ssize_t bytes_read;

    while (1) {
        display_prompt();
        fflush(stdout);

        bytes_read = get_input(&input);

        if (bytes_read == -1) {
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
        free(input);
    }

    return EXIT_SUCCESS;
}

