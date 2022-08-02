#include "main.h"

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
