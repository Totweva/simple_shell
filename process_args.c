#include "main.h"

/**
 * process_args - splits a string and stores values in an array
 * @buf: buffer
 * @args: pointer to malloced array
 * @delim: delimeter
 *
 * Return: -1 or 0
 */
int process_args(char *buf, char **args, char delim)
{
	int bufsize = MAXLIST;
	char *token;
	int index = 0;

	if (_strlen(buf) == 0)
		return (-1);

	token = _strtok(buf, delim);
	while (token)
	{
		args[index] = _strdup(token);
		index++;

		if (index >= bufsize)
		{
			/* bufsize += MAXLIST; */
<<<<<<< HEAD
			args = realloc(args, bufsize + MAXLIST);
=======
			args = _realloc(args, bufsize, bufsize + MAXLIST);
>>>>>>> d70535109f294b76bdd8646d3d18ebfc018ddf2e
			if (!args)
			{
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
		}
		free(token);
		token = _strtok(NULL, delim);
	}
	free(token);
	args[index] = NULL;
	return (0);
}
