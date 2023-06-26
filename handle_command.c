#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * is_built_in_command - Check if a command is a built-in command
 * @command: The command to check
 *
 * Return: true if the command is a built-in command,
 * false otherwise
 */
bool is_built_in_command(const char *command)
{
	if (strcmp(command, "cd") == 0 || strcmp(command, "exit") == 0)
	{
		return (true);
	}

	return (false);
}

/**
 * is_background_command - Check if a command is a background command
 * @command: The command to check
 *
 * Return: true if the command is a background command, false otherwise
 */

bool is_background_command(const char *command)
{
	size_t len = strlen(command);

	if (len > 0 && command[len - 1] == '&')
	{
		return (true);
	}

	return (false);
}

/**
 * parse_commands - Parse input into commands
 * @input: The input string to parse
 * @commands: The array to store the parsed commands
 *
 * Return: The number of commands parsed
 */

int parse_commands(char *input, char *commands[MAX_COMMANDS][MAX_ARGS])
{
	int num_commands = 0;

	char *token = strtok(input, " \n");
	int i;

	for (i = 0; i < MAX_ARGS && token != NULL; i++)
	{
		commands[num_commands][i] = strdup(token);

		token = strtok(NULL, " \n");
	}

	while (i < MAX_ARGS)
	{
		commands[num_commands][i] = NULL;
		i++;
	}

	num_commands++;

	return (num_commands);
}

/**
 * trim_whitespace - Trim leading and trailing whitespace from a string
 * @str: The string to trim
 *
 * Return: The trimmed string
 */

char *trim_whitespace(char *str)
{
	char *end;

	while (isspace((unsigned char)*str))
	{
		str++;
	}

	if (*str == '\0')
	{
		return (str);
	}

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	{
		end--;
	}
	*(end + 1) = '\0';

	return (str);
}
