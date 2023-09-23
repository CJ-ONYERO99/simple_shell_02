#include "orion_shell.h"

/**
 * initiate_orion_non_interactive - starts Orion shell in non-interactive mode
 * Return: void
 */

void initiate_orion_non_interactive(void)
{
	char *command_inputs;
	char **parsed_command;

	while ((command_inputs = orion_read_lines()) != NULL)
	{
		if (!orion_is_white_space(command_inputs))
		{
			parsed_command = parse_command_input(command_inputs, ORION_TOKEN_SEPARATOR);
			if (parsed_command[0][0] != '#')
				execute_orion_command(parsed_command);
			orion_free_command_memory(parsed_command);
		}
		free(command_inputs);
	}
}
