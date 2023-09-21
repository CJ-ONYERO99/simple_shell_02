#include "ORION_SHELL_HEADER.h"

/**
 * orion_implode - implodes array of string into one string
 * @splitted_tokens: pointer to array of tokens
 * @needle: pointer to needle
 * Return: pointer to imploded string
 */
char *orion_implode_tokens(char **splitted_tokens, char *delimeter)
{
	char *result = malloc(0);
	int splitted_token_index = 0, byteSize = 0;

	while (splitted_tokens[splitted_token_index] != NULL)
	{
		byteSize = strlen(splitted_tokens[splitted_token_index]) + 1
		+ strlen(delimeter) + 1;
		result = realloc(result, byteSize);
		if (splitted_token_index > 0)
		{
			strcat(result, delimeter);
		}

		strcat(result, splitted_tokens[splitted_token_index]);
		splitted_token_index++;
	}

	return (result);
}
