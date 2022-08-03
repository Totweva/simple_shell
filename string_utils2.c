#include "main.h"

/**
 * _strtok - splits a string and stores values in an array
 * @buf: buffer
 * @args: pointer to malloced array
 * @delim: delimeter
 */
void _strtok(char *buf, char **args, char *delim)
{
	int bufsize = MAXLIST;
	char *token;
	int index = 0;

	token = strtok(buf, delim);
	while (token)
	{
		args[index] = _strdup(token);
		index++;

		if (index >= bufsize)
		{
			bufsize += MAXLIST;
			args = realloc(args, bufsize);
			if (!args)
			{
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	args[index] = NULL;
}

