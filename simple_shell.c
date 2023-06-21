#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

char* get_input() {
    char* input = malloc(100 * sizeof(char));
    printf("Simple_shell$: ");
    fgets(input, 100, stdin);
    return input;
}

void execute_commands(char* commands[MAX_COMMANDS][MAX_ARGS], int num_commands) {
    int i;
    for (i = 0; i < num_commands; i++) {
        if (is_built_in_command(commands[i][0])) {
            if (strcmp(commands[i][0], "cd") == 0) {
                if (commands[i][1] == NULL) {
                    printf("Missing directory argument for cd command\n");
                } else {
                    if (chdir(commands[i][1]) != 0) {
                        printf("Failed to change directory\n");
                    }
                }
            } else if (strcmp(commands[i][0], "exit") == 0) {
                exit(0);
            }
        } else {
            pid_t pid = fork();
            
            if (pid == 0) {
                execvp(commands[i][0], commands[i]);
                printf("Failed to execute command: %s\n", commands[i][0]);
                exit(1);
            } else if (pid > 0) {
                if (!is_background_command(commands[i][0])) {
                    int status;
                    waitpid(pid, &status, 0);
                }
            } else {
                printf("Failed to fork process\n");
                exit(1);
            }
        }
    }
}

int main() {
    char* input;
    char* commands[MAX_COMMANDS][MAX_ARGS];
    int num_commands;
    int i, j;
    while (1) {
        input = get_input();
        num_commands = parse_commands(input, commands);
        execute_commands(commands, num_commands);
        
        for (i = 0; i < num_commands; i++) {
            for (j = 0; j < MAX_ARGS; j++) {
                free(commands[i][j]);
            }
        }
        free(input);
    }
    return 0;
}

