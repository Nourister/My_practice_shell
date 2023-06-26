#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * search_executable - Searches for the executable in
 * the directories listed in PATH
 * @command: The command to search
 *
 * Return: The full path of the executable if found,
 * NULL otherwise
 */
char *search_executable(const char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char *executable_path = NULL;

	while (token != NULL)
	{
		executable_path = malloc(strlen(token) + strlen(command) + 2);
		if (executable_path == NULL)
		{
			perror("Malloc error");
			return (NULL);
		}
		strcpy(executable_path, token);
		strcat(executable_path, "/");
		strcat(executable_path, command);

		if (access(executable_path, X_OK) == 0)
			return (executable_path);

		free(executable_path);
		token = strtok(NULL, ":");
	}

	return (NULL);
}

/**
 * execute_command - Executes a single command
 * @command: The command to execute
 */
void execute_command(const char *command)
{
	pid_t pid;
	int status;
	char *executable_path = search_executable(command);

	if (executable_path == NULL)
	{
		printf("Command not found: %s\n", command);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		free(executable_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(executable_path, (char * const*)&command, NULL) == -1)
		{
			perror("Execve error");
			free(executable_path);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(executable_path);
		return;
	}
}
