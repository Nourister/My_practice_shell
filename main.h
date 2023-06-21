#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void execute_command(char* input);
void print_environment();
void display_prompt();
void set_environment_variable(char* variable, char* value);
void unset_environment_variable(char* variable);

extern char** environ;

#endif  /* MAIN_H */

