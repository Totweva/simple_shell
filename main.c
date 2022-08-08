#include "main.h"

/**
 * sigHandler - prompts the shell upon a signal
 * @sig_input: the signal
 */
void sigHandler(int sig_input)
{
	char *new_prompt = "\n$ ";

	(void)sig_input;
	signal(SIGINT, sigHandler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * handle_exec - executes arguments
 * @args: pointer to arguments
 */
void handle_exec(char **args)
{
	int status, index;
	char *arg;
	pid_t pid;
	builtin_t funcs[] = {
		{"exit", simpsh_exit},
		{"env", simpsh_env},
		{NULL, NULL}
	};

	/* check if the first argument is a builtin */
	for (index = 0; funcs[index].name; index++)
	{
		if (_strcmp(funcs[index].name, args[0]) == 0)
			break;
	}
	if (funcs[index].f)
		funcs[index].f(args);
	
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
}

/**
 * prompt - prompts the USer

void prompt(void)
{
	write(1, "$ ", 2);
}*/

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
 * process_str - process the input from user
 * @str: string
 * @args: pointer to malloced array
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

/**
 * main - Entry to SHELL
 *
 * Return: 0 always
 */
int main(void)
{
	size_t bufsize = MAXCHAR;
	char *buf;
	char **args;
	char *prompt = "$ ", *new_line = "\n";

	signal(SIGINT, sigHandler);

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
			prompt;
		if (handle_input(buf))
			continue;

		if (process_str(buf, args) < 0)
			continue;
		free(buf);
		handle_exec(args);
		free(args);
		if (!isatty(0))
			return (0);
	}
	return (0);
}
