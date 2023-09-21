#include "orion_shell_header.h"

/**
 * orion_tokenize_str- splits string into tokens
 * @input_str: pointer to string to tokenize
 * @delimiter: pointer to delimiters
 * Return: pointer to string of token
 */
char *orion_tokenize_str(char *input_str, const char *delimiter)
{
	char *start, *end;
	static char *next_token;

	start = (input_str == NULL) ? next_token : input_str;
	start += strspn(start, delimiter);

	if (*start == '\0')
	{
		next_token = NULL;
		return (NULL);
	}

	end = start + strcspn(start, delimiter);

	if (*end != '\0')
		*end++ = '\0';

	next_token = end;
	return (start);
}
