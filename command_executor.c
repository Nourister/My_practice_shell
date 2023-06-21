#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

void execute_built_in_command(const char* command) {
    if (strcmp(command, "cd") == 0) {
        printf("Executing 'cd' command\n");
    } else if (strcmp(command, "env") == 0) {
        printf("Executing 'env' command\n");
    } else {
        printf("Unknown built-in command: %s\n", command);
    }
}

