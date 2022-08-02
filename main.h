#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXCHAR 1000 /* maximum characters suppoted */
#define MAXLIST 100 /* max comands supported */

extern char **environ;

char *read_line();

/*string function utilities */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(char *str);

/* environ function utilities */
char **_getenv(const char *str);

/* helper functions */
void free_args(char **args);

void _strtok(char *str, char **args, char *delim);

#endif /* MAIN_H */
