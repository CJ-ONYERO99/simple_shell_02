#include "orion_shell.h"

/**
 * get_command_path - gets the full path of command
 * @command: pointer to command string
 * Return: string to full path
 */

char *get_command_path(char *command)
{
	char *full_path, *system_path, *copy_of_system_path, *splitted_path;

	system_path = getenv("PATH");
	copy_of_system_path = strdup(system_path);

	/* Do PATH manipulation over here */

	splitted_path = orion_str_tokenizer(copy_of_system_path, ":");

	while (splitted_path != NULL)
	{
		full_path = malloc(sizeof(char) *
				(strlen(splitted_path) + strlen(command) + 2));
		if (full_path != NULL)
		{
			strcpy(full_path, splitted_path);
			strcat(full_path, "/");
			strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				free(copy_of_system_path);
				return (full_path);
			}
			splitted_path = orion_str_tokenizer(NULL, ":");
		}

		free(full_path);
	}

	free(copy_of_system_path);
	free(splitted_path);

	return (NULL);
}
