#include "main.h"

void set_environment_variable(char* variable, char* value) {
    if (setenv(variable, value, 1) == -1) {
        fprintf(stderr, "Failed to set environment variable.\n");
    }
}

void unset_environment_variable(char* variable) {
    if (unsetenv(variable) == -1) {
        fprintf(stderr, "Failed to unset environment variable.\n");
    }
}

void execute_command(char* input) {
    pid_t pid;
    char* command;
    char* arguments[10];
    char* path;
    char* path_token;
    int i;
    char command_path[BUFFER_SIZE];

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
        char** env = environ;
        while (*env != NULL) {
            printf("%s\n", *env);
            env++;
        }
        return;
    } else if (strcmp(arguments[0], "setenv") == 0) {
        if (i == 3) {
            set_environment_variable(arguments[1], arguments[2]);
        } else {
            fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        }
        return;
    } else if (strcmp(arguments[0], "unsetenv") == 0) {
        if (i == 2) {
            unset_environment_variable(arguments[1]);
        } else {
            fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        }
        return;
    }

    path = getenv("PATH");
    path_token = strtok(path, ":");

    while (path_token != NULL) {
        snprintf(command_path, BUFFER_SIZE, "%s/%s", path_token, arguments[0]);

        if (access(command_path, X_OK) == 0) {
            pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                /* Child process */
                execve(command_path, arguments, environ);
                perror("execve");
                exit(EXIT_FAILURE);
            } else {
                /* Parent process */
                int status;
                if (waitpid(pid, &status, 0) == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
                return;
            }
        }

        path_token = strtok(NULL, ":");
    }

    fprintf(stderr, "No such file or directory: %s\n", arguments[0]);
}
