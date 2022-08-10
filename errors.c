#include "main.h"

/**
 * num_len - number of digits in a number
 * @num: Number
 *
 * Retur: lenght
 */
int num_len(int num)
{
	unsigned int _num;
	int len = 1;

	/* check if number is negetive */
	if (num < 0)
	{
		_num = num * -1;
		len++;
	}
	else
		_num = num;

	while (_num > 9)
	{
		_num /= 10;
		len++;
	}

	return (len);
}

/**
 * _itoa - Convert integer to string
 * @num: Number
 *
 * Return: string representation of number
 */
char *_itoa(int num)
{
	char *buffer;
	unsigned int _num;
	int len = num_len(num);

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		_num = num * -1;
		buffer[0] = '-';
	}
	else
		_num = num;

	/* 
	 * write number to string backward starting before the
	 * terminating character
	 */
	len--;
	do {
		buffer[len] = (_num % 10) + '0';
		_num /= 10;
		len--;
	} while (num > 0);

	return (buffer);
}

/**
 * raise_error - writes a custom error message to stderr
 * @args: Array of arguments
 * @err: error value
 *
 * Return: error value
 */
int raise_error(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			error = error_env(args);
			break;
		case 1:
			error = error_1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = error_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] ==     '|')
				error = error_2_syntax(args);
			else
				error = error_2_cd(args);
			break;
		case 126:
			error = error_126(args);
			break;
		case 127:
			error =error_127(args);
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);
}

