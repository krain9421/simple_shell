#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 1024
#define BUILTIN 3

int getuserinput(char **buf);
int parsestring(char *text, char **parsed);
int isbuiltin(char **argv);
void loopshell(char **buf, char **argz, char **argv);
void executecom(char **argz, char **argv);

#endif

