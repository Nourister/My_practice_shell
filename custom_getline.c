#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * custom_getline - reads a line of input from the user and returns
 * a dynamically allocated string
 * Return: dynamically allocated string
 */

char *custom_getline()
{
	char c;
	int i = 0;
	int capacity = 100;
	char *buffer = malloc(capacity * sizeof(char));

	if (buffer == NULL)
	{
		perror("Memory allocation failed");
		exit(1);
	}

	while ((c = getchar()) != '\n')
	{
		if (i >= capacity - 1)
		{
			char *new_buffer = realloc(buffer, capacity * 2 * sizeof(char));

			if (new_buffer == NULL)
			{
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

	return (buffer);
}

