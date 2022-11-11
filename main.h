#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define BUFFSIZE 1024
#define PARSESIZE 40
#define BUILTIN 3

extern char **environ;

char *getuserinput();
char **parsestring(char *text);
int isbuiltin(char **argv);
void loopshell(char **argv);
void executecom(char **argz, char **argv);

#endif

