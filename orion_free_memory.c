#include "orion_shell_header.h"

/**
 * free_orion_cmd_memory - frees memory
 * Return: void
 * @parsed_cmd: pointer to memory to be freed.
 */

void free_orion_cmd_memory(char **parsed_cmd)
{
	int i;

	if (parsed_cmd != NULL)
	{
		for (i = 0; parsed_cmd[i] != NULL; i++)
		{
			free(parsed_cmd[i]);
		}

		free(parsed_cmd);
	}
}
