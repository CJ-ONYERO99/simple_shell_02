#include "orion_shell_header.h"

/**
 * orion_exit_shell - function to implement in-built exit
 * @parsed_cmd: parsed command to execute
 * Return: int
 */
int orion_exit_shell(char **parsed_cmd)
{
	int exit_status;
	char *error_message;

	if (parsed_cmd[1])
	{
		exit_status = atoi(parsed_cmd[1]);
		if (exit_status < 0)
		{
			error_message = malloc(ORION_MAX_BUFFER_SIZE * sizeof(char));

			if (error_message == NULL)
			{
				perror(orion_shell_name);
				return (1);
			}

			snprintf(error_message, 1024,"%s: 1: %s: Illegal number: %d\n", 
					orion_shell_name, "exit", exit_status);

			write(STDERR_FILENO, error_message, strlen(error_message));
			free(error_message);
		}
		else
			exit(exit_status);
		return (exit_status);
	}
	else
	{
		exit(0);
		return (0);
	}
}

/**
 * orion_print_environment - function to implement in-built env
 * @parsed_cmd: parsed command to execute
 * Return: int
 */
int orion_print_environment(char **parsed_cmd __attribute__((unused)))
{
	int orion_counter = 0;

	while (environ[orion_counter] != NULL)
	{
		printf("%s\n", environ[orion_counter]);
		orion_counter++;
	}

	return (orion_counter);
}

/**
 * orion_change_directory - function to implement in-built cd
 * @parsed_cmd: parsed command to execute
 * Return: int
 */
int orion_change_directory(char **parsed_cmd)
{
	char orion_previous_dir[1024];

	getcwd(orion_previous_dir, sizeof(orion_previous_dir));

	if (parsed_cmd[1] == NULL)
	{
		parsed_cmd[1] = getenv("HOME");
	}
	else if (strcmp(parsed_cmd[1], "-") == 0)
	{
		parsed_cmd[1] = getenv("OLDPWD");
		if (parsed_cmd[1] == NULL)
		{
			perror(orion_shell_name);
			return (1);
		}
	}

	if (chdir(parsed_cmd[1]) != 0)
	{
		perror(orion_shell_name);
	}
	else
	{
		setenv("OLDPWD", orion_previous_dir, 1);
		setenv("PWD", parsed_cmd[1], 1);
	}
	return (0);
}

/**
 * orion_echo_cmd - function to implement in-built echo
 * @parsed_cmd: parsed command to execute
 * Return: int
 */
int orion_echo_cmd(char **parsed_cmd)
{
	int orion_process_id;

	if (parsed_cmd[2])
		write(2, "Too many arguments\n", 20);
	else
	{
		if (strcmp("$$", parsed_cmd[1]) == 0)
		{
			orion_process_id = getpid();
			printf("%i\n", orion_process_id);
		}
		else if (strcmp("$?", parsed_cmd[1]) == 0)
		{
			int orion_exit_status;

			wait(&orion_exit_status);

			printf("%d", orion_exit_status);
		}
		else
		{
			printf("%s\n", parsed_cmd[1]);
		}
	}

	return (0);
}
