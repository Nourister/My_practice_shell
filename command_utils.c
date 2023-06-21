#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

void build_command_path(char* command_path, char* path_token, char* command) {
    strcpy(command_path, path_token);
    strcat(command_path, "/");
    strcat(command_path, command);
}

int is_executable(const char* command_path) {
    return (access(command_path, X_OK) == 0);
}

void execute_executable(const char* command_path, char** arguments) {
    pid_t child_pid;
    int child_status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        execv(command_path, arguments);
        perror("execv");
        exit(EXIT_FAILURE);
    } else {
        waitpid(child_pid, &child_status, 0);
    }
}

