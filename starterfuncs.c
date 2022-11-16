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
	char *tbuf = NULL;

	/*tbuf = malloc(sz * sizeof(char));*/
	/*if (tbuf == NULL)*/
		/*exit(1);*/

	bufsz = getline(&tbuf, &sz, stdin);
	if (bufsz == -1)
	{
		free(tbuf);
		exit(EXIT_FAILURE);
	}

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
	int i = 0, sz = 0;
	char *parse, *textcpy, *textcpy2;
	char **tparsed;

	if (text == NULL)
	{
		tparsed = malloc(1 * sizeof(char *));
		if (tparsed == NULL)
		{ free(tparsed), exit(1); }
		tparsed[0] = NULL;
		return (tparsed);
	}
	textcpy = _strdup(text);
	textcpy2 = _strdup(text);
	/* Get size of the array to hold paths */
	parse = strtok(textcpy, "\n");
	while (parse)
	{
		parse = strtok(NULL, "\n");
		sz++;
	}
	free(parse);
	free(textcpy);
	tparsed = malloc((sz + 1) * sizeof(char *));
	if (tparsed == NULL)
	{ free(tparsed), exit(1); }

	parse = strtok(textcpy2, "\n");
	while (parse)
	{
		tparsed[i] = _strdup(parse);
		parse = strtok(NULL, "\n");
		i++;
	}
	tparsed[i] = NULL;
	free(parse);
	free(textcpy2);

	return (tparsed);
}
	/**
	*tparsed = malloc(sz * sizeof(char *));
	*if (tparsed == NULL)
	*	exit(1);
	*
	*textcpy = _strdup(text);
	*
	*if (textcpy == NULL)
	*{
	*	tparsed[0] = NULL;
	*	free(textcpy);
	*	return (tparsed);
	*}
	*
	*parse = strtok(textcpy, "\n");
	*while (parse)
	*{
	*	tparsed[i] = _strdup(parse);
	*	parse = strtok(NULL, "\n");
	*	i++;
	*}
	*tparsed[i] = (NULL);
	*free(parse);
	*free(textcpy);
	*
	*return (tparsed);
	*/

/**
* executecom - executes a program or command
* @argz: string vector that contains the command arguments
* @argv: string vector from main
* @env: environment vector from main
*
* Return: 1 if successful
* 0 if failed
*/

int executecom(char **argz, char **argv, char **env)
{
	pid_t pid;

	if (argz[0])
	{
		pid = fork();

		if (pid == 0)
		{
			if (execve(argz[0], argz, env) == -1)
				perror(argv[0]);
			return (1);
		}
		else if (pid < 0)
		{
			wait(NULL);
			return (0);
		}

		else
		{
			wait(NULL);
			return (1);
		}
	}
	else
	{
		perror(argv[0]);
		wait(NULL);
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
	int stat = 1, i = 0, isrelative = 0;

	getcwd(cwd, sizeof(cwd));
	do {
		write(1, "sshll>", 6);
		buf = getuserinput();
		argz = parsestring(buf);
		if (argz[0] != NULL)
		{
			if (argz[0][0] != '/')
			{
				isrelative = 1;
				parsedpath = getpaths();
				path = getpath(parsedpath, argz[0], cwd);
				free(argz[0]);
				argz[0] = _strdup(path);
			}
			stat = executecom(argz, argv, env);
			free(buf), free(argz[0]), free(argz);
			if (isrelative)
			{
				free(path);
				while (parsedpath[i])
				{ free(parsedpath[i++]); }
				free(parsedpath);
			}
		}
		else
		{ free(buf), free(argz[0]), free(argz); }
	} while (stat);
}

