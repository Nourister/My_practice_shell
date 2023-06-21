#include <stdio.h>
#include <string.h>
#include "main.h"

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

void add_alias(char* name, char* value) {
    int i;
    for (i = 0; i < num_aliases; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            strcpy(aliases[i].value, value);
            return;
        }
    }

    if (num_aliases < MAX_ALIASES) {
        strcpy(aliases[num_aliases].name, name);
        strcpy(aliases[num_aliases].value, value);
        num_aliases++;
    } else {
        fprintf(stderr, "Maximum number of aliases reached\n");
    }
}

void print_aliases() {
    int i;
    for (i = 0; i < num_aliases; i++) {
        printf("%s = %s\n", aliases[i].name, aliases[i].value);
    }
}

char* get_alias_value(char* name) {
    int i;
    for (i = 0; i < num_aliases; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            return aliases[i].value;
        }
    }
    return NULL;
}

