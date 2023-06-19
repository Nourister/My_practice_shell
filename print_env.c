#include "main.h"

void print_environment() {
    char** env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

