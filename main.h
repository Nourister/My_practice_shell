#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt();
char *find_executable(char *command);
void execute_command(char* input);
void print_environment();

extern char **environ;

#endif  /* MAIN_H */

