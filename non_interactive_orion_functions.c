#include "shell.h"

/**
 * start_orion_non_interactive - starts ORION shell in non-interactive mode
 * Return: void
 */

void start_orion_non_interactive(void)
{
	char *orion_cmd_input;
	char **orion_parsed_cmd;

	while ((orion_cmd_input = orion_read_input_lines()) != NULL)
	{
		if (!orion_is_whitespace(orion_cmd_input))
		{
			orion_parsed_cmd = orion_parse_cmd(orion_cmd_input, ORION_TOKEN_SEPARATOR);
			if (orion_parsed_cmd[0][0] != '#')
				execute_orion_cmd(orion_parsed_cmd);
			free_orion_cmd_memory(orion_parsed_cmd);
		}
		free(orion_cmd_input);
	}
}
