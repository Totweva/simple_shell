#include "main.h"

/**
 * get_env_value - get value of environment variable
 * @str: string
 *
 * Return: pointer to value
 */
char *get_env_value(char *str)
{
	char *token;
	char *new_str, *delim = "=";

	new_str = _strdup(str);

	token = strtok(new_str, delim);
	if (token)
	{
		token = strtok(NULL, delim);
		return (token);
	}
	free(new_str);
	return (NULL);
}

/**
 * _getenv - gets the environment variables from PATH
 * @str: string to search for in environment
 *
 * Return: pointer to environment variable or NULL
 */
char **_getenv(const char *str)
{
	int i, len = _strlen(str);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(str, environ[i], len) == 0)
			return (&environ[i]);
	}
	return (NULL);
}
