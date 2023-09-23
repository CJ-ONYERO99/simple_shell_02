#include "orion_shell_header.h"

/**
 * is_orion_interactive - Checks whether the shell is in interactive mode.
 *
 * Return: 1 if interactive, 0 otherwise.
 */
int is_orion_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * execute_orion_cmd - Function to execute a command.
 *
 * @parsed_cmd: Pointer to parsed commands.
 */
void execute_orion_cmd(char **parsed_cmd)
{
	OrionBuiltIn orion_built_in_functions[4] = {
		{"exit", orion_exit_shell},
		{"env", orion_print_environment},
		{"cd", orion_change_directory},
		{"echo", orion_echo_cmd}
	};
	int orion_built_in_num, is_built_in = 0, orion_counter = 0;

	orion_built_in_num = sizeof(orion_built_in_functions) /
						sizeof(orion_built_in_functions[0]);

	while (orion_counter < orion_built_in_num)
	{
		if (strcmp(parsed_cmd[0], orion_built_in_functions[orion_counter].name) == 0)
		{
			is_built_in = 1;
			orion_built_in_functions[orion_counter].command(parsed_cmd);
			break;
		}
		orion_counter++;
	}

	if (is_built_in == 0)
	{
		perform_orion_actions(parsed_cmd);
	}
}

/**
 * orion_is_white_space - Check if a string contains only whitespace characters
 *
 * @input_str: Pointer to the string to check.
 *
 * Return: 1 if whitespace, 0 otherwise.
 */
int orion_is_white_space(char *input_str)
{
	int is_white = 1, orion_counter = 0;

	while (input_str[orion_counter])
	{
		if (!isspace(input_str[orion_counter]))
		{
			is_white = 0;
			break;
		}

		orion_counter++;
	}

	return (is_white);
}
