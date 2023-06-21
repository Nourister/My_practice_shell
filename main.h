#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ALIASES 10
#define BUFFER_SIZE 256

typedef struct {
    char name[BUFFER_SIZE];
    char value[BUFFER_SIZE];
} Alias;

extern Alias aliases[MAX_ALIASES];
extern int num_aliases;
extern pid_t pid;

void display_prompt();
ssize_t get_input(char** input);
void handle_commands(char* command);

void change_directory(char* directory);
void print_current_directory();
void handle_exit_command();
int is_env_command(char** arguments);
void handle_env_command();
int is_setenv_command(char** arguments);
void handle_setenv_command(char** arguments);
int is_unsetenv_command(char** arguments);
void handle_unsetenv_command(char** arguments);
void build_command_path(char* command_path, char* path_token, char* command);
int is_executable(const char* command_path);
void execute_executable(const char* command_path, char** arguments);
void handle_no_such_file_or_directory_error(char* command);

void add_alias(char* name, char* value);
void print_aliases();
char* get_alias_value(char* name);

void print_environment();
void set_environment_variable(const char* variable, const char* value);
void unset_environment_variable(const char* variable);

#endif /* MAIN_H */

