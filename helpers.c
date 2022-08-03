#include "main.h"

/**
 * free_args - free args memory
 * @args: double pointer to args
 */
void free_args(char **args)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
	{
		free(args[i]);
	}
}
