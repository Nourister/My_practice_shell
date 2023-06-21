#include "main.h"

void change_directory(char* directory) {
    char* home_directory = getenv("HOME");
    char* previous_directory = getenv("PWD");
    char* current_directory;

    if (directory == NULL) {
        if (home_directory == NULL) {
            fprintf(stderr, "cd: No $HOME variable set\n");
            return;
        }
        directory = home_directory;
    } else if (strcmp(directory, "-") == 0) {
        if (previous_directory == NULL) {
            fprintf(stderr, "cd: No previous directory\n");
            return;
        }
        directory = previous_directory;
    }

    if (chdir(directory) != 0) {
        perror("cd");
        return;
    }

    current_directory = getcwd(NULL, 0);
    if (current_directory == NULL) {
        perror("getcwd");
        return;
    }

    setenv("PWD", current_directory, 1);
    free(current_directory);
}

