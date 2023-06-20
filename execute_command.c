#include "main.h"

void execute_command(char *input) {
    pid_t pid;
    char *command;
    char *arguments[10];
    char *path;
    char *path_token;
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
        arguments[i] = NULL; /* Set the last element to NULL */

        if (strcmp(arguments[0], "exit") == 0) {
            /* Handle exit command */
            int exit_status = EXIT_SUCCESS;
            if (arguments[1] != NULL) {
                exit_status = atoi(arguments[1]);
            }
            exit(exit_status);
        } else if (strcmp(arguments[0], "env") == 0) {
            /* Handle env command */
            char **env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
            exit(EXIT_SUCCESS);
        } else if (strcmp(arguments[0], "setenv") == 0) {
            /* Handle setenv command */
            if (arguments[1] == NULL || arguments[2] == NULL) {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                exit(EXIT_FAILURE);
            }
            if (setenv(arguments[1], arguments[2], 1) != 0) {
                fprintf(stderr, "Failed to set environment variable\n");
            }
            exit(EXIT_SUCCESS);
        } else if (strcmp(arguments[0], "unsetenv") == 0) {
            /* Handle unsetenv command */
            if (arguments[1] == NULL) {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                exit(EXIT_FAILURE);
            }
            if (unsetenv(arguments[1]) != 0) {
                fprintf(stderr, "Failed to unset environment variable\n");
            }
            exit(EXIT_SUCCESS);
        } else if (strcmp(arguments[0], "cd") == 0) {
            /* Handle cd command */
            char *dir = arguments[1];
            if (dir == NULL) {
                dir = getenv("HOME");
                if (dir == NULL) {
                    fprintf(stderr, "cd: No HOME environment variable set\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(dir, "-") == 0) {
                dir = getenv("OLDPWD");
                if (dir == NULL) {
                    fprintf(stderr, "cd: No OLDPWD environment variable set\n");
                    exit(EXIT_FAILURE);
                }
                printf("%s\n", dir);
            }
            if (chdir(dir) != 0) {
                perror("cd");
            } else {
                char current_dir[BUFFER_SIZE];
                if (getcwd(current_dir, BUFFER_SIZE) != NULL) {
                    setenv("PWD", current_dir, 1);
                    setenv("OLDPWD", getenv("PWD"), 1);
                } else {
                    perror("getcwd");
                }
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

        fprintf(stderr, "No such file or directory: %s\n", arguments[0]);
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
