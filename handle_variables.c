#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"
/**
 * display_prompt - displays the prompt simple_shell$
 * Return: void
 */
void display_prompt(void)
{
	printf("Simple_shell$ ");
}


/**
 * replace_variable - Replaces a variable in a
 * command with a given value
 * @command: The command string
 * @variable: The variable to replace
 * @value: The value to replace with
 * Return: 0(success)
 */

void replace_variable(char *command, const char *variable, const char *value)
{
	char *variable_ptr = strstr(command, variable);

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

void handle_variables(char *command, int last_status)
{
	pid_t pid;
	char pid_str[16];

	pid = getpid();
	snprintf(pid_str, sizeof(pid_str), "%d", pid);
	replace_variable(command, "$$", pid_str);

	replace_variable(command, "$?", last_status == 0 ? "0" : "1");
}

