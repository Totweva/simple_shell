#include "main.h"

/**
 * handle_exec - executes arguments
 * @args: pointer to arguments
 */
void handle_exec(char **args)
{
	int status, (*builtin_func_ptr)(char **);
	char *arg;
	pid_t pid;

	builtin_func_ptr = get_builtin(args[0]);

	if (builtin_func_ptr)
		builtin_func_ptr(args);

	/* if it isn't a builtin find path to executable */
	arg = get_exec_path(args);
	if (!arg)
	{
		perror("error");
		return;
	}
	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, environ) < 0)
			perror("error");
		free_args(args);
		_exit(EXIT_SUCCESS);
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
}

/**
 * prompt - prompts the USer
 */
void prompt(void)
{
	write(STDIN_FILENO, "$ ", 2);
}

/**
 * handle_input - handle user input stored in buffer
 * @buf: pointer to buffer
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
 * main - Entry to SHELL
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 always
 */
int main(int argc, char *argv[])
{
	size_t bufsize = MAXCHAR;
	char *buf;
	char **args;

	prog_name = argv[0];
	hist = 1;
	signal(SIGINT, sigHandler);

	if (argc != 1)
	{
		return(0);
	}
	while (1)
	{
		args = malloc(MAXLIST);
		buf = malloc(bufsize);
		if (!buf || !args)
		{
			perror("Allocation error");
			return (-1);
		}
		if (isatty(0))
			prompt();
		if (handle_input(buf))
			continue;

		if (process_args(buf, args, ' ') < 0)
			continue;
		free(buf);
		handle_exec(args);
		free_args(args);
		if (!isatty(0))
			return (0);
	}
	return (0);
}
