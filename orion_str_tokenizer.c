#include "orion_shell.h"

/**
 * orion_str_tokenizer - splits a string into tokens
 * @input_string: pointer to the string to tokenize
 * @separator: pointer to delimiters
 * Return: pointer to the tokenized string
 */

char *orion_str_tokenizer(char *input_string, const char *separator)
{
	char *initial, *terminal;
	static char *final_word;

	initial = (input_string == NULL) ? final_word : input_string;
	initial += strspn(initial, separator);

	if (*initial == '\0')
	{
		final_word = NULL;
		return (NULL);
	}

	terminal = initial + strcspn(initial, separator);

	if (*terminal != '\0')
		*terminal++ = '\0';

	final_word = terminal;
	return (initial);
}
