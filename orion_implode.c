#include "orion_shell.h"

/**
 * orion_implode - implodes array of strings into one string
 * @splitted_tokens: pointer to array of tokens
 * @needle: pointer to needle
 * Return: pointer to imploded string
 */

char *orion_implode(char **splitted_tokens, char *needle)
{
	char *imploded_string = malloc(0);
	int splitted_token_index = 0, byteSize = 0;

	while (splitted_tokens[splitted_token_index] != NULL)
	{
		byteSize = strlen(splitted_tokens[splitted_token_index])
			+ 1 + strlen(needle) + 1;
		imploded_string = realloc(imploded_string, byteSize);
		if (splitted_token_index > 0)
		{
			strcat(imploded_string, needle);
		}

		strcat(imploded_string, splitted_tokens[splitted_token_index]);
		splitted_token_index++;
	}

	return (imploded_string);
}
