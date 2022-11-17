#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
/*#include <errno.h>*/
#include <signal.h>
#define BUFFSIZE 1024
#define PARSESIZE 40
#define BUILTIN 3

/*extern char **environ;*/

char *getuserinput();
char **parsestring(char *text);
int isbuiltin(char **argv);
void loopshell(char **argv, char **env);
int executecom(char **argz, char **argv, char **env);
char *_getenv(const char *name, char **env);
char **getpaths(char **env);
char *getpath(char **parsedpath, char *exe, const char *src);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(const char *str);
char *_strdup(char *src);
int _strcmp(char *s1, char *s2);
void signalhandler(int sig);

#endif

