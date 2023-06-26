#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * interactive_mode - Displays the interactive mode of the
 * shell program
 * Return: 0(success)
 */
void interactive_mode(void)
{
	char *input;
	char *commands[MAX_COMMANDS][MAX_ARGS];
	int num_commands;
	int i;

	while (1)
	{
		printf("Simple_shell$ ");

		input = custom_getline();

		if (input == NULL)
		{
			printf("\n");
			break;
		}

		if (input[0] == '#')
		{
			continue;
		}

		num_commands = parse_commands(input, commands);
		execute_commands(commands, num_commands);

		for (i = 0; i < num_commands; i++)
		{
			int j;

			for (j = 0; j < MAX_ARGS; j++)
			{
				free(commands[i][j]);
			}
		}
		free(input);
	}
}

/**
 * main - Entry point to a program
 * @argc: The number of command-line arguments
 * @argv: An array of strings representing thecommand-line arguments
 * Return: 0 (success)
 */
int main(int argc, char *argv[])
{
	char line[100];
	char *commands[MAX_COMMANDS][MAX_ARGS];
	int num_commands;
	int i;

	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");

		if (file == NULL)
		{
			printf("Failed to open file: %s\n", argv[1]);
			return (1);
		}

		while (fgets(line, sizeof(line), file))
		{
			line[strcspn(line, "\n")] = '\0';

			num_commands = parse_commands(line, commands);
			execute_commands(commands, num_commands);

			for (i = 0; i < num_commands; i++)
			{
				int j;

				for (j = 0; j < MAX_ARGS; j++)
				{
					free(commands[i][j]);
				}
			}
		}

		fclose(file);
		return (0);
	}

	interactive_mode();

	return (0);
}
