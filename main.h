#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 10
#define MAX_INPUT_SIZE 100

char* custom_getline();
void display_prompt();
void replace_variable(char* command, const char* variable, const char* value);
void handle_variables(char* command, int last_status);
void execute_commands(char* commands[MAX_COMMANDS][MAX_ARGS], int num_commands);
void execute_command(const char* command);
bool is_built_in_command(const char* command);
bool is_background_command(const char* command);
int parse_commands(char* input, char* commands[MAX_COMMANDS][MAX_ARGS]);
char* trim_whitespace(char* str);
char* search_executable(const char* command);
void interactive_mode();

#endif /* MAIN_H */

