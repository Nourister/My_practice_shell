#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

void execute_command(char* input) {
    int i;
    char* arguments[256];
    char* token;

    token = strtok(input, " ");
    i = 0;
    while (token != NULL) {
        arguments[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    arguments[i] = NULL;

    if (arguments[0] != NULL) {
        if (strcmp(arguments[0], "exit") == 0) {
            handle_exit_command(arguments);
        } else if (is_env_command(arguments)) {
            handle_env_command();
        } else if (is_setenv_command(arguments)) {
            handle_setenv_command(arguments);
        } else if (is_unsetenv_command(arguments)) {
            handle_unsetenv_command(arguments);
        } else {
            char command_path[BUFFER_SIZE];
            char* path_env = getenv("PATH");
            char* path_token;

            if (path_env != NULL) {
                path_token = strtok(path_env, ":");
                while (path_token != NULL) {
                    build_command_path(command_path, path_token, arguments[0]);
                    if (is_executable(command_path)) {
                        execute_executable(command_path, arguments);
                        return;
                    }
                    path_token = strtok(NULL, ":");
                }
            }

            handle_no_such_file_or_directory_error(arguments[0]);
        }
    }
}

void handle_no_such_file_or_directory_error(char* command) {
    fprintf(stderr, "%s: command not found\n", command);
}

