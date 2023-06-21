#include "main.h"
#include <stdio.h>
#include <string.h>

void handle_exit_command() {
    exit(0);
}

void handle_env_command() {
    print_environment();
}

void handle_setenv_command(char** arguments) {
    if (arguments[1] != NULL && arguments[2] != NULL) {
        set_environment_variable(arguments[1], arguments[2]);
    } else {
        printf("Error: Invalid arguments for setenv command\n");
    }
}

void handle_unsetenv_command(char** arguments) {
    if (arguments[1] != NULL) {
        unset_environment_variable(arguments[1]);
    } else {
        printf("Error: Invalid argument for unsetenv command\n");
    }
}

void print_environment() {
    extern char** environ;
    int i;
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}


