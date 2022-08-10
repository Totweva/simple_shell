#include "main.h"

/**
 * _strtok - tokenize a string
 * @str: string
 * @delim: delimeter
 *
 * Return: pointer to token
 */
char *_strtok(char *str, char delim)
{
	static char *input;
	int len = _strlen(str) + 1, i = 0;
	char *result;

	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);

	len = _strlen(input) + 1;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);

	for (; input[i] != '\0'; i++)
	{
		if (input[i] != delim)
			result[i] = input[i];
		else
		{
			result[i] = '\0';
			input = input + i + 1;
			return (result);
		}
	}
	result[i] = '\0';
	input = NULL;

	return (result);
}
