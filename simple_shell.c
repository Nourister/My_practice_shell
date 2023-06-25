#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

char* custom_getline() {
    char c;
    int i = 0;
    int capacity = 100;
    char* buffer = malloc(capacity * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    while ((c = getchar()) != '\n') {
        if (i >= capacity - 1) {
            char* new_buffer = realloc(buffer, capacity * 2 * sizeof(char));
            if (new_buffer == NULL) {
                perror("Memory reallocation failed");
                free(buffer);
                exit(1);
            }
            buffer = new_buffer;
            capacity *= 2;
        }
        buffer[i++] = c;
    }

    buffer[i] = '\0';

    return buffer;
}

/**
 * execute_commands - Executes a list of commands
 * @commands: The commands array
 * @num_commands: The number of commands
 * Return: 0(success)
 */

void execute_commands(char* commands[MAX_COMMANDS][MAX_ARGS], int num_commands)
{
    int i;
    int last_status = 0;

    for (i = 0; i < num_commands; i++)
    {
        char* command = commands[i][0];

        if (command == NULL || command[0] == '#')
        {
            continue;
        }

	if (strcmp(command, "exit") == 0)
	{
		exit(0);
	}

	if (strcmp(command, "env") == 0)
	{
		char** env = __environ;
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		continue;
	}

        if (is_built_in_command(command))
        {
            if (strcmp(command, "cd") == 0)
            {
                if (commands[i][1] == NULL)
                {
                    printf("Missing directory argument for cd command\n");
                }
                else
                {
                    if (chdir(commands[i][1]) != 0)
                    {
                        printf("Failed to change directory\n");
                    }
                }
            }
            else if (strcmp(command, "exit") == 0)
            {
                exit(0);
            }
        }
        else
        {
            pid_t pid = fork();

            if (pid == 0)
            {
                handle_variables(command, last_status);
                execvp(command, commands[i]);
                printf("Command not found: %s\n", command);
                exit(1);
            }
            else if (pid > 0)
            {
                if (!is_background_command(command))
                {
                    int status;
                    waitpid(pid, &status, 0);
                    last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
                }
            }
            else
            {
                printf("Failed to fork process\n");
                exit(1);
            }
        }
    }
}

void interactive_mode() {
    char* input;
    char* commands[MAX_COMMANDS][MAX_ARGS];
    int num_commands;
    int i;

    while (1) {
        printf("Simple_shell$ ");

        input = custom_getline();

        if (input == NULL) {
            printf("\n");
            break;
        }

        if (input[0] == '#') {
            continue;
        }

        num_commands = parse_commands(input, commands);
        execute_commands(commands, num_commands);

        for (i = 0; i < num_commands; i++) {
            int j;
            for (j = 0; j < MAX_ARGS; j++) {
                free(commands[i][j]);
            }
        }
        free(input);
    }
}

/**
 * main - Entry point to a program
 * @argc: The number of command-line arguments
 * An array of strings representing the
 * command-line arguments
 * The exit status of the program
 */

int main(int argc, char* argv[]) {
    char line[100];
    char* commands[MAX_COMMANDS][MAX_ARGS];
    int num_commands;
    int i;

    if (argc == 2) {
        FILE* file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Failed to open file: %s\n", argv[1]);
            return 1;
        }

        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';

            num_commands = parse_commands(line, commands);
            execute_commands(commands, num_commands);

            for (i = 0; i < num_commands; i++) {
                int j;
                for (j = 0; j < MAX_ARGS; j++) {
                    free(commands[i][j]);
                }
            }
        }

        fclose(file);
        return 0;
    }

    interactive_mode();

    return 0;
}
