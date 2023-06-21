#include "main.h"
#include <stdlib.h>

void set_environment_variable(const char* variable, const char* value) {
    setenv(variable, value, 1);
}

void unset_environment_variable(const char* variable) {
    unsetenv(variable);
}

