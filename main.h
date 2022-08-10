#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>


#define MAXCHAR 1000 /* maximum characters suppoted */
#define MAXLIST 100 /* max comands supported */
#define UNUSED(x) (void)(x)



extern char **environ;
char *prog_name;
int hist;



/**
 * struct Builtins - Struct for defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */

typedef struct Builtins
{
	char *name;
	int (*f)(char **argv);

} builtin_t;



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



/* builtin utils */
int (*get_builtin(char *command))(char **args);
int simpsh_exit(char **args);
int simpsh_env(char **args);


/* environ function utilities */
char **_getenv(const char *str);
char *get_env_value(char *str);


/* helper functions */
void free_args(char **args);

int process_args(char *buf, char **args, char delim);
void _getline(char *buf, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strtok(char *str, char delim);
char *get_exec_path(char **args);
void handle_exec(char **args);
void prompt(void);
int handle_input(char *buf);
int process_str(char *str, char **args);
void sigHandler(int sig_input);



#endif /* MAIN_H */
