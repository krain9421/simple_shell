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
	char *tbuf;

	tbuf = malloc(sz * sizeof(char));
	if (tbuf == NULL)
		exit(1);

	bufsz = getline(&tbuf, &sz, stdin);
	if (bufsz == -1)
		exit(EXIT_FAILURE);

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
	char *parse, *textcpy;
	char **tparsed;

	tparsed = malloc(sz * sizeof(char *));
	if (tparsed == NULL)
		exit(1);

	textcpy = _strdup(text);

	if (textcpy == NULL)
	{
		tparsed[0] = NULL;
		free(textcpy);
		return (tparsed);
	}

	parse = strtok(text, "\n");
	while (parse)
	{
		tparsed[i] = _strdup(parse);
		parse = strtok(NULL, "\n");
		i++;
	}
	tparsed[i] = NULL;
	free(parse);
	free(textcpy);

	return (tparsed);
}

/**
* executecom - executes a program or command
* @argz: string vector that contains the command arguments
* @argv: string vector from main
*
* Return: 1 if successful
* 0 if failed
*/

int executecom(char **argz, char **argv)
{
	pid_t pid;

	if (argz[0])
	{
		pid = fork();

		if (pid == 0)
		{
			if (execve(argz[0], argz, NULL) == -1)
				perror(argv[0]);
			return (1);
		}
		else if (pid < 0)
			return (0);

		else
		{
			wait(NULL);
			return (1);
		}
	}
	else
	{
		perror(argv[0]);
		return (1);
	}
}

/**
* loopshell - runs the custom shell program in a loop
* @argv: string vector from main
* @env: environment vector from main
*
* Return: void
*/

void loopshell(char **argv, char **env)
{
	char *buf, *path, cwd[PATH_MAX];
	char **argz, **parsedpath;
	int stat = 1;

	getcwd(cwd, sizeof(cwd));
	do {
		write(1, "sshll>", 6);
		buf = getuserinput();
		argz = parsestring(buf);
		if (argz[0] != NULL)
		{
			if (argz[0][0] != '/')
			{
				parsedpath = getpaths(env);
				path = getpath(parsedpath, argz[0], cwd);
				argz[0] = path;
			}
			stat = executecom(argz, argv);
			free(buf);
			while (*argz)
			{ free(*argz++); }
			free(argz);
			while (*parsedpath)
			{ free(*parsedpath++); }
			free(parsedpath);
		}
		else
		{
			free(buf);
			while (*argz)
			{ free(*argz++); }
			free(argz);
		}
	} while (stat);
}

