#include "main.h"

ssize_t get_input(char** input) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_index = 0;
    static ssize_t bytes_read = 0;

    size_t input_index;
    char current_char;
    size_t input_size = 1;

    if (buffer_index >= (size_t)bytes_read) {
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer_index = 0;
        if (bytes_read == 0) {
            return -1;
        }
    }

    input_index = 0;
    current_char = buffer[buffer_index++];
    if (current_char == '\n') {
        *input = NULL;
        return 0;
    }

    *input = malloc(input_size * sizeof(char));

    while (current_char != '\n') {
        (*input)[input_index++] = current_char;

        if (input_index >= input_size) {
            input_size *= 2;
            *input = realloc(*input, input_size * sizeof(char));
            if (*input == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        if (buffer_index >= (size_t)bytes_read) {
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytes_read == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            buffer_index = 0;
            if (bytes_read == 0) {
                break;
            }
        }

        current_char = buffer[buffer_index++];
    }

    (*input)[input_index] = '\0';
    return input_index;
}

