#include "orion_shell_header.h"

/**
 * perform_orion_actions - function to execute entered commands
 * @parsed_args: parsed inputted arguments
 */
void perform_orion_actions(char **parsed_args)
{
	char *full_cmd_path;

	if (is_orion_cmd_available(parsed_args[0]) == 1)
	{
		execute_orion_system_call(parsed_args[0], parsed_args);
	}
	else
	{
		full_cmd_path = orion_get_cmd_path(parsed_args[0]);
		execute_orion_system_call(full_cmd_path, parsed_args);
		free(full_cmd_path);
	}
}

/**
 * execute_orion_system_call - function to execute entered commands
 * @cmd_to_execute: actual command to be executed
 * @parsed_args: parsed inputted arguments
 */
void execute_orion_system_call(char *cmd_to_execute, char **parsed_args)
{
	pid_t orion_process_id;
	char *imploded_cmd;

	if (cmd_to_execute != NULL)
	{
		orion_process_id = fork();
		if (orion_process_id == 0)
		{
			execve(cmd_to_execute, parsed_args, NULL);
			perror(orion_shell_name);
		}
		else if (orion_process_id < 0)
		{
			perror(strcat(orion_shell_name, " :1 : "));
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		imploded_cmd = orion_implode_tokens(parsed_args, " ");
		orion_write_error_msg(imploded_cmd);
		free(imploded_cmd);
	}
}

/**
 * is_orion_cmd_available - checks if supplied command path is available
 * @full_cmd_path: command full path
 * Return: int
 */
int is_orion_cmd_available(char *full_cmd_path)
{
	int is_available = 0;

	if (access(full_cmd_path, F_OK) == 0 && access(full_cmd_path, X_OK) == 0)
	{
		is_available = 1;
	}
	return (is_available);
}

/**
 * orion_write_error_msg - prints error message to stderr
 * @cmd_str: pointer to command as string
 * Return: int
 */
int orion_write_error_msg(char *cmd_str)
{
	char *error_message;

	error_message = malloc(ORION_MAX_BUFFER_SIZE * sizeof(char));

	if (error_message == NULL)
	{
		perror(orion_shell_name);
		return (1);
	}

	snprintf(error_message, 1024, "%s: 1: %s: command not found\n",
			orion_shell_name, cmd_str);

	write(STDERR_FILENO, error_message, strlen(error_message));
	free(error_message);

	return (0);
}
