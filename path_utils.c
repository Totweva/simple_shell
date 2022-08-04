#include "main.h"

/**
 * get_exec_path - get executable path
 * @args: pointer to arguments
 *
 * Return: path to executable or NULL
 */
char *get_exec_path(char **args)
{
	char **path = NULL, *delim = ":", *path_value;
	size_t index = 0;
	char *cwd = getcwd(NULL, 0);
	struct stat sb;
	char **dirs = malloc(sizeof(char) * MAXLIST);

	path = _getenv("PATH");
	if (!dirs || !path)
		return (NULL);
	path_value = get_env_value(*path);
	_strtok(path_value, dirs, delim);
	while (dirs[index])
	{
		chdir(dirs[index]);
		if (stat(args[0], &sb) == 0)
		{
			dirs[index] = _strcat(dirs[index], "/");
			args[0] = _strcat(dirs[index], args[0]);
			break;
		}
		index++;
	}
	chdir(cwd);
	free(dirs);
	return (args[0]);
}
