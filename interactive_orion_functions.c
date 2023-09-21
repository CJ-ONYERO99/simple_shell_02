#include "orion_shell_header.h"

/**
 * start_orion_interactive - start Orion shell in interactive mode
 * Return: void
 */

void start_orion_interactive(void)
{
	char *cmd_input;
	size_t orion_linecap = 0;
	int shell_status = 1;
	ssize_t getline_result;
	char **parsed_cmd;

	while (shell_status == 1)
	{
		printf("$ ");

		getline_result = getline(&cmd_input, &orion_linecap, stdin);

		if (getline_result == -1)
		{
			free(cmd_input);
			shell_status = -1;
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (!orion_is_white_space(cmd_input))
			{
				parsed_cmd = orion_parse_cmd(cmd_input, ORION_TOKEN_SEPARATOR);
				if (parsed_cmd[0][0] != '#')
					execute_orion_cmd(parsed_cmd);
				free_orion_cmd_memory(parsed_cmd);
			}
		}
	}
}
