#include "orion_shell.h"

/**
 * initiate_orion_interactive - starts Orion shell in interactive mode
 * Return: void
 */

void initiate_orion_interactive(void)
{
	char *command_input;
	size_t orion_linecap = 0;
	int shell_status = 1;
	ssize_t getline_result;
	char **parsed_command;

	while (shell_status == 1)
	{
		printf("$ ");

		getline_result = getline(&command_input, &orion_linecap, stdin);

		if (getline_result == -1)
		{
			free(command_input);
			shell_status = -1;
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (!orion_is_white_space(command_input))
			{
				parsed_command = parse_command_input(command_input, ORION_TOKEN_SEPARATOR);
				if (parsed_command[0][0] != '#')
					execute_orion_command(parsed_command);
				orion_free_command_memory(parsed_command);
			}

		}
	}

	/* free(command_input); */
}
