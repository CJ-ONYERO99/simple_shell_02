#include "orion_shell.h"

/**
 * orion_exit - function to implement in-built exit
 * @parsed_commands: parsed command to execute
 * Return: int
 */
int orion_exit(char **parsed_commands)
{
	int exit_status;
	char *error_message;

	if (parsed_commands[1])
	{
		exit_status = atoi(parsed_commands[1]);
		if (exit_status < 0)
		{
			error_message = malloc(ORION_MAX_BUFFER_SIZE * sizeof(char));

			if (error_message == NULL)
			{
				perror(orion_shell_name);
				return (1);
			}

			snprintf(error_message, 1024,
					"%s: 1: %s: Illegal number: %d\n",
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
 * orion_env - function to implement in-built env
 * @parsed_commands: parsed command to execute
 * Return: int
 */
int orion_env(char **parsed_commands __attribute__((unused)))
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
 * orion_cd - function to implement in-built cd
 * @parsed_commands: parsed command to execute
 * Return: int
 */
int orion_cd(char **parsed_commands)
{
	char orion_previous_dir[1024];

	getcwd(orion_previous_dir, sizeof(orion_previous_dir));

	if (parsed_commands[1] == NULL)
	{
		parsed_commands[1] = getenv("HOME");
	}
	else if (strcmp(parsed_commands[1], "-") == 0)
	{
		parsed_commands[1] = getenv("OLDPWD");
		if (parsed_commands[1] == NULL)
		{
			perror(orion_shell_name);
			return (1);
		}
	}

	if (chdir(parsed_commands[1]) != 0)
	{
		perror(orion_shell_name);
	}
	else
	{
		setenv("OLDPWD", orion_previous_dir, 1);
		setenv("PWD", parsed_commands[1], 1);
	}
	return (0);
}

/**
 * orion_echo - function to implement in-built echo
 * @parsed_commands: parsed command to execute
 * Return: int
 */
int orion_echo(char **parsed_commands)
{
	int orion_process_id;

	if (parsed_commands[2])
		write(2, "Too many arguments\n", 20);
	else
	{
		if (strcmp("$$", parsed_commands[1]) == 0)
		{
			orion_process_id = getpid();
			printf("%i\n", orion_process_id);
		}
		else if (strcmp("$?", parsed_commands[1]) == 0)
		{
			int orion_exit_status;

			wait(&orion_exit_status);

			printf("%d", orion_exit_status);
		}
		else
		{
			printf("%s\n", parsed_commands[1]);
		}
	}

	return (0);
}
