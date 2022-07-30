#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXCHAR 1000 /* maximum characters suppoted */
#define MAXLIST 100 /* max comands supported */

char *read_line();

#endif /* MAIN_H */
