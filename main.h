#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 10

char* get_input();
bool is_built_in_command(const char* command);
bool is_background_command(const char* command);
int parse_commands(char* input, char* commands[MAX_COMMANDS][MAX_ARGS]);
void execute_commands(char* commands[MAX_COMMANDS][MAX_ARGS], int num_commands);

#endif /* MAIN_H */

