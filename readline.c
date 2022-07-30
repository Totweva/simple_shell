#include "main.h"

char *read_line()
{
	int bufsize = MAXCHAR;
	int i = 0, c;
	char *buf = malloc(sizeof(char) * bufsize);
	
	if (!buf)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = getchar();
		
		if (c == EOF || c == '\n')
		{
			buf[i] = '\0';
			return buf;
		}
		else
		{
			buf[i] = c;
		}
		i++;
		
		if (i >= bufsize)
		{
			bufsize += MAXCHAR;
			buf = realloc(buf, bufsize);
			if (!buf)
			{
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
		}
	}
}
