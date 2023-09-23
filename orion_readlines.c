#include "orion_shell.h"

/**
 * orion_read_lines - reads lines from a file or stdin
 * Return: pointer to lines read as a string
 */

char *orion_read_lines(void)
{
	char *input_commands = NULL;
	size_t orion_buffer_size = 0;

	if (getline(&input_commands, &orion_buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input_commands);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(input_commands);
			perror(orion_shell_name);
			exit(EXIT_FAILURE);
		}
	}
	return (input_commands);
}
