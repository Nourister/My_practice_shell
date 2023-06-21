#include "main.h"
#include <stdio.h>
#include <string.h>

int is_exit_command(char** arguments) {
    return (strcmp(arguments[0], "exit") == 0);
}

int is_env_command(char** arguments) {
    return (strcmp(arguments[0], "env") == 0);
}

int is_setenv_command(char** arguments) {
    return (strcmp(arguments[0], "setenv") == 0);
}

int is_unsetenv_command(char** arguments) {
    return (strcmp(arguments[0], "unsetenv") == 0);
}
