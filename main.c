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

	new_str = _strcpy(new_str, str);

	token = strtok(new_str, delim);
	if (token)
	{
		token = strtok(NULL, delim);
		return (token);
	}
	return (NULL);
}

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
	char **dirs = malloc(MAXLIST);

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
	return args[0];
}

/**
 * handle_exec - executes arguments
 * @args: pointer to arguments
 */
void handle_exec(char **args)
{
	int status;
	char *arg;
	pid_t pid;

	arg = get_exec_path(args);
	if (!arg)
	{
		perror("error");
		return;
	}
	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, NULL) < 0)
			perror("error");
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror("error");
	}
	else
	{
		do {
			wait(&status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return;
}

/**
 * prompt - prompts the USer
 */
void prompt()
{
	write(1, "$ ", 2);
}

/**
 * handle_input
 * @buf: pointer to buffer
 * @bufsize: buffer size
 *
 * Return: 0 always
 */
int handle_input(char *buf)
{
	size_t bufsize = MAXCHAR;
	size_t index = 0;
	int input = getline(&buf, &bufsize, stdin);

	if (input < 0)
	{
		perror("couldn't get line");
		return (-1);
	}
	while (buf[index] != '\0' || buf[index] != EOF || buf[index] != '\n')
	{
		if (buf[index] == EOF || buf[index] == '\n')
		{
			buf[index] = '\0';
			return (0);
		}
		index++;
	}

	return (0);
}

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

/**
 * process_str - process the input from user
 * @str: string
 * %args: pointer to malloced array
 *
 * Return: 0 always
 */
int process_str(char *str, char **args)
{
	if (_strlen(str) == 0)
		return (-1);

	_strtok(str, args, " ");
	return (0);
}

/***
 * main - Entry to SHELL
 *
 * Return: 0 always
 */
int main()
{
	size_t bufsize = MAXCHAR;
	char *buf;
	char **args = malloc(MAXLIST);

	while(1)
	{
		buf = malloc(bufsize);
		if (!buf)
		{
			perror("Allocation error");
			return (-1);
		}
		prompt();
		if (handle_input(buf))
			continue;

		printf("%s\n", buf);
		if (process_str(buf, args) < 0)
			continue;
		printf("%s\n", args[0]);
		handle_exec(args);
		free(buf);
		free(args);
	}
	return (0);
}
