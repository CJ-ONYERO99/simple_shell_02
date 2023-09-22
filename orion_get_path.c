#include "orion_shell_header.h"

/**
 * orion_get_cmd_path - gets the full path of a command
 * @cmd: pointer to command string
 * Return: string to full path
 */
char *orion_get_cmd_path(char *cmd)
{
	char *full_path, *system_path, *copy_of_system_path, *splitted_path;

	system_path = getenv("PATH");
	copy_of_system_path = strdup(system_path);

	/* Do PATH manipulation here */

	splitted_path = orion_tokenize_str(copy_of_system_path, ":");

	while (splitted_path != NULL)
	{
		full_path = malloc(sizeof(char) * (strlen(splitted_path) + strlen(cmd) + 2));
		if (full_path != NULL)
		{
			strcpy(full_path, splitted_path);
			strcat(full_path, "/");
			strcat(full_path, cmd);

			if (access(full_path, X_OK) == 0)
			{
				free(copy_of_system_path);
				return (full_path);
			}
			splitted_path = orion_tokenize_str(NULL, ":");
		}

		free(full_path);
	}

	free(copy_of_system_path);
	free(splitted_path);

	return (NULL);
}
