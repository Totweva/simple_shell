#include "main.h"

/**
 * free_args - free args memory
 * @args: double pointer to args
 * @first_item: pointer to first item in args
 */
void free_args(char **args)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
	{
		printf("%s\n", args[i]);
		free(args[i]);
		printf("%s\n", args[i]);
	}
}
