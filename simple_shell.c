#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * get_input - Reads input from the user
 * Return: The input string
 */

char* get_input()
{
	char* input = malloc(100 * sizeof(char));
	printf("Simple_shell$ ");

	if (fgets(input, 100, stdin) == NULL)
	{
		free(input);
		return (NULL);
	}

	return input;
}

/**
 * replace_variable - Replaces a variable in a
 * command with a given value
 * @command: The command string
 * @variable: The variable to replace
 * @value: The value to replace with
 * Return: 0(success)
 */

void replace_variable(char* command, const char* variable, const char* value)
{
	char* variable_ptr = strstr(command, variable);
	while (variable_ptr != NULL)
	{
		strncpy(variable_ptr, value, strlen(value));
		variable_ptr = strstr(command, variable);
	}
}

/**
 * handle_variables - Handles variables in a command
 * @command: The command string
 * @last_status: The last command status
 * Return: 0(success)
 */

void handle_variables(char* command, int last_status)
{
	pid_t pid;
	char pid_str[16];

	pid = getpid();
	snprintf(pid_str, sizeof(pid_str), "%d", pid);
	replace_variable(command, "$$", pid_str);

	replace_variable(command, "$?", last_status == 0 ? "0" : "1");
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

/**
 * main - Entry point to a program
 * @argc: The number of command-line arguments
 * @argv: An array of strings representing the command-line arguments
 * Return: The exit status of the program
 */

int main(int argc, char* argv[])
{
    char* input;
    char* commands[MAX_COMMANDS][MAX_ARGS];
    int num_commands;
    int i;
    char line[100];

    if (argc == 2)
    {
        FILE* file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Failed to open file: %s\n", argv[1]);
            return 1;
        }

        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line, "\n")] = '\0';

            num_commands = parse_commands(line, commands);
            execute_commands(commands, num_commands);

            for (i = 0; i < num_commands; i++)
            {
                int j;
                for (j = 0; commands[i][j] != NULL; j++)
                {
                    free(commands[i][j]);
                    commands[i][j] = NULL;
                }
            }
        }

        fclose(file);
        return 0;
    }

    while (1)
    {
        printf("$ ");
        input = get_input();
        if (input == NULL)
            break;

        num_commands = parse_commands(input, commands);
        execute_commands(commands, num_commands);

        for (i = 0; i < num_commands; i++)
        {
            int j;
            for (j = 0; commands[i][j] != NULL; j++)
            {
                free(commands[i][j]);
                commands[i][j] = NULL;
            }
        }

        free(input);
    }

    return 0;
}
