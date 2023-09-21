#include "orion_shell_header.h"

/**
 * orion_read_input_lines - reads lines from a file or stdin
 * Return: pointer to lines read as a string
 */
char *orion_read_input_lines(void)
{
	char *input_cmd = NULL;
	size_t orion_buffer_size = 0;

	if (getline(&input_cmd, &orion_buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input_cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(input_cmd);
			perror(orion_shell_name);
			exit(EXIT_FAILURE);
		}
	}
	return (input_cmd);
}
