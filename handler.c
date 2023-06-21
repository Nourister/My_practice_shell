#include "main.h"

int execute_command(char* input);

void handle_commands(char* input) {
    char* command;
    char* command_token;

    command = strtok(input, ";");

    while (command != NULL) {
        command_token = strtok(command, " ");

        if (command_token != NULL) {
            if (strcmp(command_token, "cd") == 0) {
                char* argument = strtok(NULL, " ");
                change_directory(argument);
            } else if (strcmp(command_token, "alias") == 0) {
                char* argument = strtok(NULL, " ");
                if (argument != NULL) {
                    if (strcmp(argument, "-p") == 0) {
                        print_aliases();
                    } else {
                        char* value = strtok(NULL, " ");
                        add_alias(argument, value);
                    }
                }
            } else if (strcmp(command_token, "&&") == 0) {
                if (execute_command(command + 3) != 0) {
                    break;
                }
            } else if (strcmp(command_token, "||") == 0) {
                if (execute_command(command + 3) == 0) {
                    break;
                }
            } else {
                execute_command(command);
            }
        }

        command = strtok(NULL, ";");
    }
}

