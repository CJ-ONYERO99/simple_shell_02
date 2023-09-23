#include "orion_shell_header.h"

/**
 * is_orion_interactive - checks whether shell is in interactive mode
 * Return: 1 or 0 as int
 */
int is_orion_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * execute_orion_cmd - function to execute command
 * @parsed_cmd: pointer to parsed commands
 * Return: void
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
		if (strcmp(parsed_cmd[0],
					orion_built_in_functions[orion_counter].name) == 0)
		{
			is_built_in = 1;
			orion_built_in_functions[orion_counter].command(parsed_cmd);
			break;
		}
		orion_counter++;
	}

	if (is_built_in == 0)
	{
		handle_non_builtin_cmds(parsed_cmd);
	}
}

/**
 * handle_non_builtin_cmds - handle non-built-in commands
 * @parsed_cmd: parsed command to execute
 * Return: void
 */
void handle_non_builtin_cmds(char **parsed_cmd)
{
	if (strcmp(parsed_cmd[0], "ls") == 0 && strcmp(parsed_cmd[1], "-l") == 0)
	{
		execute_ls_l();
	}
	else
	{
		perform_orion_actions(parsed_cmd);
	}
}

/**
 * execute_ls_l - execute the ls -l command
 * @parsed_cmd: parsed command to execute
 * Return: void
 */
void execute_ls_l(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == 0)
	{
		execlp("ls", "ls", "-l", (char *)NULL);
		perror("ls -l");
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
	{
		perror("Fork failed");
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}

/**
 * orion_is_white_space - checks if
 * string contains only whitespace characters
 * @input_string: pointer to string to check
 * Return: 1 if whitespace else 0
 */
int orion_is_white_space(char *input_string)
{
	int is_white = 1, orion_counter = 0;

	while (input_string[orion_counter])
	{
		if (!isspace(input_string[orion_counter]))
		{
			is_white = 0;
			break;
		}

		orion_counter++;
	}

	return (is_white);
}
