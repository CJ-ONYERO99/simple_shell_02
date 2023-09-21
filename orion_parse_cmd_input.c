#include "orion_shell_header.h"

/**
 * orion_parse_cmd - separate inputted cmd into an array of strings
 * @input_cmd: pointer to the cmd string
 * @separator: pointer to the delimiter
 * Return: pointer that points to the newly parsed array of strings
 */
char **orion_parse_cmd(char *input_cmd, char *separator)
{
	int buffer_size = ORION_TOKEN_BUFFER_SIZE;
	char *copy_of_cmd;
	int index_of_token = 0;
	char **splitted_tokens = malloc(buffer_size * sizeof(char *));
	char *cmd_token;

	copy_of_cmd = strdup(input_cmd);

	if (!splitted_tokens)
	{
		perror("orion_shell: could not allocate memory for tokens\n");
		exit(EXIT_FAILURE);
	}

	cmd_token = orion_tokenize_str(copy_of_cmd, separator);

	while (cmd_token != NULL)
	{
		splitted_tokens[index_of_token] = strdup(cmd_token);
		index_of_token++;

		if (index_of_token >= buffer_size)
		{
			buffer_size += buffer_size;
			splitted_tokens = realloc(splitted_tokens, buffer_size * sizeof(char *));
			if (!splitted_tokens)
			{
				perror("orion_shell: could not re-allocate memory for tokens\n");
				exit(EXIT_FAILURE);
			}
		}

		cmd_token = orion_tokenize_str(NULL, separator);
	}

	splitted_tokens[index_of_token] = NULL;
	free(copy_of_cmd);
	return (splitted_tokens);
}
