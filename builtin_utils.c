#include "main.h"

/**
 * get_builtin - Matches a command with a corresponding
 *               shellby builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args)
{
	builtin_t funcs[] = {
		{ "exit", simpsh_exit },
		{ "env", simpsh_env },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * simpsh_exit - Causes normal process termination
 *                for the shellby shell.
 * @args: An array of arguments containing the exit value.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 */
int simpsh_exit(char **args)
{
	free(args);
	exit(EXIT_SUCCESS);
}

/**
 * simpsh_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 */
int simpsh_env(char **args)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	UNUSED(args);
	return (0);
}
