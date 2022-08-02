#include "main.h"

char *get_value(char *str)
{
	char *token;
	char *new_str;

	new_str = _strcpy(new_str, str);

	token = strtok(new_str, "=");
	if (token)
	{
		token = strtok(NULL, "=");
		printf("====%s====\n", token);
		return (token);
	}
	return (NULL);
}

char *search(char **args)
{
	char **path = NULL, *path_value;
	size_t i = 0;
	char *cwd = getcwd(NULL, 0);
	struct stat sb;
	char **dirs = malloc(sizeof(char) * MAXLIST);

	if (!dirs)
	{
		free(dirs);
		exit(EXIT_FAILURE);
	}
	
	path = _getenv("PATH");
	if (!path)
		exit(EXIT_FAILURE);
	/* remove 'PATH=' from path */
	path_value = get_value(*path);
	_strtok(path_value, dirs, ":");
	while (dirs[i] != NULL)
	{
		chdir(dirs[i]);
		if (stat(args[0], &sb) == 0)
		{
			/* ========= Not EFFICIENT ========== */
			dirs[i] = _strcat(dirs[i], "/");
			args[0] = _strcat(dirs[i], args[0]);
			break;
		}
		i++;
	}
	chdir(cwd);
	return args[0];
}

/**
 * handle_exec - a function that creates a child process and checks for error
 * @argc: command arguments passed to the child process
 * Return: if sucessful
 */
void handle_exec(char **args)
{
	int status;
	char *arg;
	pid_t pid;

	arg = search(args);
	printf("-----%s------\n", arg);
	/*
	printf("get here 1");
	arg = search(args);
	if (!arg)
	{
		perror("error");
		return;
	}
	*/
	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, NULL) < 0)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		do {
			wait(&status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return;
}



int handle_input(char *str)
{
	size_t n = 10;
	char *buf = read_line();

	if (strlen(buf) != 0)
	{
		strcpy(str, buf);
	}
	free(buf);
	return (0);
}

void _strtok(char *str, char **args, char *delim)
{
	int bufsize = MAXLIST;
	char *token;
	int i;

	i = 0;
	token = strtok(str, delim);
	while (token)
	{
		/* ====== implement strdup or use strcpy */
		args[i] = strdup(token);
		i++;

		if (i >= bufsize)
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
	args[i] = NULL;
	printf("pointer? %p\n", args[0]);
}

int process_str(char *str, char **args)
{
	_strtok(str, args, " ");
	return (0);
}

int main(void)
{
	char *input;
	char **args = malloc(sizeof(char) * MAXLIST);

	if (!args)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		input = malloc(sizeof(char) * MAXCHAR);
		if (!input)
		{
			perror("error");
			return (-1);
		}
		write(1, "$ ", 2);
		if (handle_input(input))
			continue;

		process_str(input, args);
		handle_exec(args);

		free(input);
		free(args);
	}
	return (0);
}
