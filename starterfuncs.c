#include "main.h"
#include <stdio.h>

/**
* signalhandler - catches a signal
* @sig: int
*
* Return: void
**/

void signalhandler(int sig)
{
	signal(sig, SIG_IGN);
	printf("OUCH, you hit Ctrl-C!\n");
	exit(EXIT_SUCCESS);
}

/**
* getuserinput - stores user input in a string
*
* Return: character pointer with stored input
**/

char *getuserinput()
{
	size_t sz = BUFFSIZE;
	char *tbuf;

	tbuf = malloc(sz * sizeof(char));
	if (tbuf == NULL)
	{ free(tbuf), exit(EXIT_FAILURE); }

	if (getline(&tbuf, &sz, stdin) != -1)
	{
		return (tbuf);
	}
	free(tbuf);
	exit(EXIT_SUCCESS);
	/* Usage: exit */
	/**
	*if (_strcmp(tbuf, "exit\n") == 0)
	*{
	*	free(tbuf);
	*	exit(EXIT_SUCCESS);
	*}
	*/
}

/**
* parsestring - parses through a string
* @text: string to be parsed
* @cwd: current working directory
*
* Return: address to the pointer that holds
* all the parsed strings
**/

char **parsestring(char *text, char *cwd)
{
	int i = 0, sz = PARSESIZE, isrelative = 0;
	char *parse, *parse2, *textcpy2, *textcpy, *path = NULL;
	char **tparsed, **parsedpath = NULL;

	if (text[0] != '/' && text != NULL)
	{
		isrelative = 1;
		textcpy = strdup(text);
		parse2 = strtok(textcpy, "\n "), parsedpath = getpaths(environ);
		path = getpath(parsedpath, parse2, cwd);
		free(parse2), free(parsedpath);
	}
	if (text == NULL)
	{
		tparsed = malloc(1 * sizeof(char *));
		if (tparsed == NULL)
		{ free(tparsed), exit(1); }
		tparsed[0] = NULL;

		return (tparsed);
	}
	textcpy2 = _strdup(text);
	tparsed = malloc((sz) * sizeof(char *));
	if (tparsed == NULL)
	{ free(tparsed), exit(1); }
	parse = strtok(textcpy2, "\n ");
	while (parse)
	{
		tparsed[i] = _strdup(parse);
		if (tparsed[i] == NULL)
		{ free(tparsed[i]), free(tparsed), exit(1); }
		parse = strtok(NULL, "\n ");
		i++;
	}
	tparsed[i] = NULL;
	free(parse), free(textcpy2);
	if (isrelative && tparsed[0] != NULL)
	{ free(tparsed[0]), tparsed[0] = (path); }
	return (tparsed);
}

/**
* executecom - executes a program or command
* @argz: string vector that contains the command arguments
* @argv: string vector from main
* @env: environment vector from main
*
* Return: 1 if successful
* 0 if failed
**/

int executecom(char **argz, char **argv, char **env)
{
	pid_t pid;

	if (argz[0] && _strcmp(argz[0], "exit") == 0)
	{ return (0); }
	if (argz[0])
	{
		pid = fork();
		/*printf("fork() called\n");*/

		if (pid == 0)
		{
		/*printf("Child[%d] started from Parent[%d]\n", getpid(), getppid());*/
			if (execve(argz[0], argz, env) == -1)
			{
				perror(argv[0]);
				free(argz[0]), free(argz);
			}

			/*printf("Child[%d] ended\n", getpid());*/
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			wait(NULL);
			return (0);
		}

		else
		{
			/*printf("Parent[%d] started\n", getpid());*/
			wait(NULL);
			/*printf("Parent[%d] ended\n", getpid());*/
		}
	}
	else
	{
		perror(argv[0]);
		wait(NULL);
	}
	return (1);
}

/**
* loopshell - runs the custom shell program in a loop
* @argv: string vector from main
* @env: environment vector from main
*
* Return: void
**/

void loopshell(char **argv, char **env)
{
	char *buf, cwd[PATH_MAX];
	char **argz;
	int stat = 1, i = 0;

	getcwd(cwd, sizeof(cwd));
	do {
		if (isatty(STDIN_FILENO))
		{ write(1, "#cisfun$ ", 9); }
		buf = getuserinput();
		if (_strcmp(buf, "\n") != 0)
		{
			argz = parsestring(buf, cwd);
			/**
			*if (_strcmp(argz[0], "exit") == 0)
			*	while (argz[i])
			*	{ free(argz[i++]); }
			*	free(argz);
			*	i = 0;
			*	free(buf);
			*	_exit(EXIT_SUCCESS);
			*/
			if (argz[0][0] != '/')
			{
				/*isrelative = 1;*/
				/*parsedpath = getpaths(env);*/
				/*path = getpath(parsedpath, argz[0], cwd);*/
				/*free(argz[0]);*/
				/*argz[0] = _strdup(path);*/
			}
			stat = executecom(argz, argv, env);
			free(buf);
			while (argz[i])
			{ free(argz[i++]); }
			free(argz);
			i = 0;
		}
		else
		{ free(buf);/*, free(argz[0]), free(argz);*/ }
	} while (stat);
}

