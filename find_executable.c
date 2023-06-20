#include "main.h"

char *find_executable(char *command) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");

    char *executable_path = NULL;

    while (token != NULL) {
        executable_path = malloc(strlen(token) + strlen(command) + 2);
        if (executable_path == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        sprintf(executable_path, "%s/%s", token, command);
        if (access(executable_path, X_OK) == 0) {
            free(path_copy);
            return executable_path;
        }
        free(executable_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
