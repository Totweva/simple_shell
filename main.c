#include "main.h"

void handle_exec(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error");
		return;
	}
	else if (pid == 0)
	 {
		if (execve(*args, args, NULL) < 0)
			perror("Error");
		exit(0);
	}
	else
	{
		wait(NULL);
		return;
	}
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
	int i;

	for (i = 0; i < MAXLIST; i++)
	{
		args[i] = strsep(&str, " ");
		if (!args[i])
			break;
		if (strlen(args[i]) == 0)
			i--;
	}
}

int process_str(char *str, char **args)
{
	parse_space(str, args);
	return (0);
}

int main()
{
	char input[MAXCHAR], *args[MAXLIST];

	while (1)
	{
		write(1, "$ ", 2);
		if (handle_input(input))
			continue;

		process_str(input, args);
		handle_exec(args);
	}
	return (0);
}
