#include "main.h"


/**
 * handle_exec - a function that creates a child process and checks for error
 * @argc: command arguments passed to the child process
 * Return: if sucessful
 */

void handle_exec(char **args)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(*args, args, NULL) < 0)
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

void parse_space(char *str, char **args)
{
	int bufsize = MAXLIST;
	char *token;
	int i;
	int tok_len;

	i = 0;
	token = strtok(str, " ");
	while (token)
	{
		args[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += MAXLIST;
			args = realloc(args, bufsize * sizeof(char));
			if (!args)
			{
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/*
	for (i = 0; i < MAXLIST; i++)
	{
		args[i] = strsep(&str, " ");
		if (!args[i])
			break;
		if (strlen(args[i]) == 0)
			i--;
	}
	*/
}

int process_str(char *str, char **args)
{
	parse_space(str, args);
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
