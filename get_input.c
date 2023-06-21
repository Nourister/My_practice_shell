#include "main.h"
#include <stdio.h>
#include <stdlib.h>

ssize_t get_input(char** input) {
    size_t bufsize = 0;
    return getline(input, &bufsize, stdin);
}

