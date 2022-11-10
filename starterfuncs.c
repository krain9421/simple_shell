#include "main.h"
#include <stdio.h>

/**
* getuserinput - stores user input in a string
*
* Return: character pointer with stored input
*/

char *getuserinput()
{
	size_t sz = BUFFSIZE;
	int bufsz;
	char *tbuf = malloc(BUFFSIZE * sizeof(char));

	if (tbuf == NULL)
		exit(1);

	bufsz = getline(&tbuf, &sz, stdin);
	if (bufsz == -1)
		exit(EXIT_SUCCESS);

	bufsz -= 1;
	if (bufsz == 0)
	{
		tbuf = NULL;
		return (tbuf);
	}
	tbuf[bufsz] = '\0';
	return (tbuf);
}

/**
* parsestring - parses through a string
* @text: string to be parsed
*
* Return: address to the pointer that holds
* all the parsed strings
*/

char **parsestring(char *text)
{
	int i = 0, sz = PARSESIZE;
	char *parse;
	char **tparsed = malloc(sz * sizeof(char *));

	if (tparsed == NULL)
		exit(1);

	if (text == NULL)
	{
		tparsed[0] = NULL;
		return (tparsed);
	}

	parse = strtok(text, "\0");
	while (parse)
	{
		tparsed[i] = parse;
		parse = strtok(NULL, " ");
		i++;
	}
	tparsed[i] = NULL;

	return (tparsed);
}

/**
* executecom - executes a program or command
* @argz: string vector that contains the command arguments
* @argv: string vector from main
*
* Return: void
*/

void executecom(char **argz, char **argv)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execve(argz[0], argz, NULL) == -1)
			perror(argv[0]);
	}
	else if (pid < 0)
		perror(argv[0]);

	else
		wait(&status);
}

/**
* loopshell - runs the custom shell program in a loop
* @argv: string vector from main
*
* Return: void
*/

void loopshell(char **argv)
{
	char *buf;
	char **argz;

	while (1)
	{
		write(1, "sshll>", 6);
		buf = getuserinput();
		if (buf != NULL)
		{
			argz = parsestring(buf);
			executecom(argz, argv);
			free(buf);
			free(argz);
		}
		else
			free(buf);
	}
}

