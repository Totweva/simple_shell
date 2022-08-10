#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char **args;
	int n = 3, i;

	args = malloc(n);

	for (i = 0; i < n; i++)
	{
		args[i] = malloc(n);
		strcpy(args[i], "NG");
	}
	for (i = 0; i < n; i++)
	{
		free(args[i]);
	}
	free(args);
	return (0);
}
