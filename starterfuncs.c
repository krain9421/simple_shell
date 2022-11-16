#include "main.h"
#include <stdio.h>

/**
* signalhandler - catches a signal
* @sig: int
*
* Return: void
*/

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
*/

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
*
* Return: address to the pointer that holds
* all the parsed strings
*/

char **parsestring(char *text)
{
	int i = 0, sz = PARSESIZE;
	char *parse, *textcpy2;
	char **tparsed;

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

	parse = strtok(textcpy2, "\n");
	while (parse)
	{
		tparsed[i] = _strdup(parse);
		if (tparsed[i] == NULL)
		{ free(tparsed[i]), free(tparsed), exit(1); }
		parse = strtok(NULL, "\n");
		i++;
	}
	tparsed[i] = NULL;
	free(parse);
	free(textcpy2);

	return (tparsed);
}
	/**
	 *textcpy = _strdup(text);
	 *parse = strtok(textcpy, "\n");
	 *while (parse)
	 *{
	 *parse = strtok(NULL, "\n");
	 *sz++;
	 *}
	 *free(parse);
	 *free(textcpy);
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
*/

void loopshell(char **argv, char **env)
{
	char *buf, *path = NULL, cwd[PATH_MAX];
	char **argz, **parsedpath = NULL;
	int stat = 1, i = 0, isrelative = 0;

	getcwd(cwd, sizeof(cwd));
	do {
		write(1, "#cisfun$ ", 9);
		buf = getuserinput();
		argz = parsestring(buf);
		if (argz[0] != NULL)
		{
			if (argz[0][0] != '/')
			{
				/*isrelative = 1;*/
				/*parsedpath = getpaths();*/
				/*path = getpath(parsedpath, argz[0], cwd);*/
				/*free(argz[0]);*/
				/*argz[0] = _strdup(path);*/
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

