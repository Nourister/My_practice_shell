#include "main.h"

void execute_command(char* input) {
    pid_t pid;
    char* command;
    char* arguments[10];
    char* path;
    char* path_token;
    int i;
    char command_path[BUFFER_SIZE];

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */

        command = strtok(input, " ");
        i = 0;
        while (command != NULL && i < 10) {
            arguments[i++] = command;
            command = strtok(NULL, " ");
        }
        arguments[i] = NULL;  /* Set the last element to NULL */

        if (strcmp(arguments[0], "exit") == 0) {
            /* Handle exit command */
            exit(EXIT_SUCCESS);
        } else if (strcmp(arguments[0], "env") == 0) {
            /* Handle env command */
            char** env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
            exit(EXIT_SUCCESS);
        }

        path = getenv("PATH");
        path_token = strtok(path, ":");

        while (path_token != NULL) {
            snprintf(command_path, BUFFER_SIZE, "%s/%s", path_token, arguments[0]);

            if (access(command_path, X_OK) == 0) {
                execve(command_path, arguments, environ);
                perror("execve");
                exit(EXIT_FAILURE);
            }

            path_token = strtok(NULL, ":");
        }

        printf("No such file or directory: %s\n", arguments[0]);
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

