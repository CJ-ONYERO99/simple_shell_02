#include "orion_shell_header.h"

/**
 * orion_handle_file - Handles the passed file.
 * @file_name: Pointer to hold the file_name.
 *
 * Return: void.
 */
void orion_handle_file(char *file_name)
{
	char **parsed_command;
	char orion_file_buffer[ORION_MAX_BUFFER_SIZE];
	ssize_t bytes_read;
	int file_handler = open(file_name, O_RDONLY);

	if (file_handler == -1)
	{
		perror("Error opening the file");
		return;
	}
	else
	{
		while ((bytes_read = read(file_handler, orion_file_buffer,
						sizeof(orion_file_buffer))) >
				0)
		{
			orion_file_buffer[bytes_read] = '\0';
			if (!orion_is_white_space(orion_file_buffer))
			{
				parsed_command = orion_parse_cmd(orion_file_buffer, ORION_TOKEN_SEPARATOR);
				execute_orion_cmd(parsed_command);
				free_orion_cmd_memory(parsed_command);
			}
		}

		if (bytes_read == -1)
		{
			perror(orion_shell_name);
			close(file_handler);
			return;
		}
	}

	close(file_handler);
}

/**
 * orion_process_file - Processes a file.
 * @file_name: Pointer to filename.
 *
 * Return: void.
 */
void orion_process_file(char *file_name)
{
	char *error_message;
	struct stat orion_file_struct;

	if (access(file_name, F_OK) == -1)
	{
		error_message = malloc(ORION_MAX_BUFFER_SIZE * sizeof(char));

		if (error_message == NULL)
		{
			perror(orion_shell_name);
			exit(EXIT_FAILURE);
		}

		snprintf(error_message, ORION_MAX_BUFFER_SIZE,
				 "%s: 0: Can't open %s\n",
				 orion_shell_name, file_name);

		write(STDERR_FILENO, error_message, strlen(error_message));
		free(error_message);
		exit(127);
	}

	if (stat(file_name, &orion_file_struct) == -1)
	{
		perror("Error getting file information");
		exit(EXIT_FAILURE);
	}

	if (orion_file_struct.st_size == 0)
	{
		/* fprintf(stderr, "File is empty\n"); */
		exit(EXIT_SUCCESS);
	}

	orion_handle_file(file_name);
}
