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
            if (i > 1) {
                int status = atoi(arguments[1]);
                exit(status);
            } else {
                exit(EXIT_SUCCESS);
            }
        } else if (strcmp(arguments[0], "env") == 0) {
            /* Handle env command */
            print_environment();
            exit(EXIT_SUCCESS);
        } else if (strcmp(arguments[0], "setenv") == 0) {
            /* Handle setenv command */
            if (i == 3) {
                setenv(arguments[1], arguments[2], 1);
            } else {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            }
            exit(EXIT_SUCCESS);
        } else if (strcmp(arguments[0], "unsetenv") == 0) {
            /* Handle unsetenv command */
            if (i == 2) {
                unsetenv(arguments[1]);
            } else {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
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

