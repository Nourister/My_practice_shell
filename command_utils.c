#include "main.h"
#include <stdio.h>
#include <string.h>

bool is_built_in_command(const char* command) {
    
    if (strcmp(command, "cd") == 0 || strcmp(command, "exit") == 0) {
        return true;
    }
    
    return false;
}

bool is_background_command(const char* command) {
    
    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '&') {
        return true;
    }
    
    return false;
}

int parse_commands(char* input, char* commands[MAX_COMMANDS][MAX_ARGS]) {
    int num_commands = 0;
    
    char* token = strtok(input, " \n");
    int i;
    for (i = 0; i < MAX_ARGS && token != NULL; i++) {
        commands[num_commands][i] = strdup(token);
        
        token = strtok(NULL, " \n");
    }
    
    while (i < MAX_ARGS) {
        commands[num_commands][i] = NULL;
        i++;
    }
    
    num_commands++;
    
    return num_commands;
}

