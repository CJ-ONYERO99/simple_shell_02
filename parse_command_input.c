#include "orion_shell.h"

/**
 * parse_command_input - separates inputted command into an array of strings
 * @command_input: pointer to the command string
 * @orion_separator: pointer to the delimiter
 * Return: pointer that points to the newly parsed array of strings
 */
char **parse_command_input(char *command_input, char *orion_separator)
{
	char *copy_of_command;
	int index_of_token = 0;
	int buffer_size = ORION_TOKEN_BUFFER_SIZE;
	char **splitted_tokens = malloc(buffer_size * sizeof(char *));
	char *command_token;

	copy_of_command = strdup(command_input);

	if (!splitted_tokens)
	{
		perror("tsh: could not allocate memory for tokens \n");
		exit(EXIT_FAILURE);
	}

	command_token = orion_str_tokenizer(copy_of_command, orion_separator);

	while (command_token != NULL)
	{
		splitted_tokens[index_of_token] = strdup(command_token);
		index_of_token++;

		if (index_of_token >= buffer_size)
		{
			buffer_size += buffer_size;
			splitted_tokens = realloc(splitted_tokens, buffer_size * sizeof(char *));

			if (!splitted_tokens)
			{
				perror("tsh: could not re-allocate memory for tokens \n");
				exit(EXIT_FAILURE);
			}
		}

		command_token = orion_str_tokenizer(NULL, orion_separator);
	}

	splitted_tokens[index_of_token] = NULL;
	free(copy_of_command);
	return (splitted_tokens);
}
