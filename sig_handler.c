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
