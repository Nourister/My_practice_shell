#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * execute_commands - Executes a list of commands
 * @commands: The commands array
 * @num_commands: The number of commands
 * Return: 0(success)
 */
void execute_commands(char *commands[MAX_COMMANDS][MAX_ARGS], int num_commands)
{
	int i, last_status = 0;

	for (i = 0; i < num_commands; i++)
	{
		char *command = commands[i][0];

		if (command == NULL || command[0] == '#')
			continue;

		if (strcmp(command, "exit") == 0)
			exit(0);

		if (strcmp(command, "env") == 0)
		{
			char **env = __environ;

			while (*env)
			{
				printf("%s\n", *env++);
				continue;
			}
		}

		if (is_built_in_command(command))
		{
			if (strcmp(command, "cd") == 0)
			{
				if (commands[i][1] == NULL)
					printf("Missing directory argument for cd command\n");
				else if (chdir(commands[i][1]) != 0)
					printf("Failed to change directory\n");
			}
			else if (strcmp(command, "exit") == 0)
				exit(0);
		}
		else
		{
			pid_t pid = fork();

			if (pid == 0)
			{
				handle_variables(command, last_status);
				execvp(command, commands[i]);
				printf("No such file or directory: %s\n", command);
				exit(1);
			}
			else if (pid > 0 && !is_background_command(command))
			{
				int status;

				waitpid(pid, &status, 0);
				last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
			}
			else if (pid < 0)
			{
				printf("Failed to fork process\n");
				exit(1);
			}
		}
	}
}
