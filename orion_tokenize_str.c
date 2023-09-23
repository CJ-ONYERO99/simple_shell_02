#include "orion_shell_header.h"

/**
 * orion_tokenize_str - Splits a string into tokens.
 * @input_str: Pointer to the string to tokenize.
 * @delimiter: Pointer to delimiters.
 *
 * Return: Pointer to the tokenized string.
 */
char *orion_tokenize_str(char *input_str, const char *delimiter)
{
	char *token;
	static char *next_token;
	char *start, *end;

	start = (input_str == NULL) ? next_token : input_str;
	start += strspn(start, delimiter);

	if (*start == '\0')
	{
		next_token = NULL;
		return (NULL);
	}

	end = start + strcspn(start, delimiter);

	token = malloc(strlen(start) + 1);

	if (token == NULL)
	{
		return (NULL);
	}

	if (*end != '\0')
		*end++ = '\0';

	strcpy(token, start);
	next_token = end;
	return (token);
}
