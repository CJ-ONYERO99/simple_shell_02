#include "shell.h"

/**
 * main - main entry to shell
 * @argc: argument count
 * @argv: string arguments
 * Return: 0 for success
 */

int main(int argc, char *argv[])
{
	orion_shell_name = argv[0] == NULL ? "tsh" : argv[0];

	if (argc == 2)
	{
		process_orion_file(argv[1]);
	}
	else
	{
		if (is_orion_interactive() == 1)
		{
			start_orion_interactive();
		}
		else
		{
			start_orion_non_interactive();
		}
	}
	return (0);
}
