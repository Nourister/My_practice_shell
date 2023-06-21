#include "main.h"

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t bytes_read;

    while (1) {
        printf("simple_shell$ ");
        fflush(stdout);

        bytes_read = getline(&input, &input_size, stdin);

        if (bytes_read == -1) {
            if (feof(stdin)) {
                printf("\n");
                break;
            } else {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        input[bytes_read - 1] = '\0';

        execute_command(input);
    }

    free(input);

    return 0;
}
