#include "main.h"
#include <stdio.h>

/**
* _getenv - gets an environment variable
* @name: variable name
*
* Return: string containing variable value
*/

char *_getenv(const char *name)
{
	int i = 0, j = 0;
	char *finalpath;

	while (environ[i])
	{
		for (; name[j]; j++)
		{
			if (name[j] == environ[i][j])
			{ continue; }
			else
			{ break; }
		}
		if (name[j] == '\0')
		{
			finalpath = _strdup(environ[i] + _strlen(name) + 1);
			return (finalpath);
		}
		i++;
	}
	return (NULL);
}

/**
* getpaths - stores all the path values in an array
*
* Return: string array containing each path
*/

char **getpaths()
{
	char *parse, *pathvalue, *pathvalue2;
	int i = 0, sz = 0;
	char **parsedpath;

	/* Getting the size of the array to hold paths */
	pathvalue2 = _getenv("PATH");
	parse = strtok(pathvalue2, ":");
	while (parse != NULL)
	{
		parse = strtok(NULL, ":");
		sz++;
	}
	free(parse);
	free(pathvalue2);

	parsedpath = malloc((sz + 1) * sizeof(char *));
	if (parsedpath == NULL)
	{ free(parsedpath), exit(EXIT_FAILURE); }

	pathvalue = _getenv("PATH");
	parse = strtok(pathvalue, ":");
	while (parse != NULL)
	{
		parsedpath[i] = _strdup(parse);
		if (parsedpath[i] == NULL)
		{ free(parsedpath[i]), exit(EXIT_FAILURE); }
		parse = strtok(NULL, ":");
		i++;
	}
	parsedpath[i] = NULL;
	free(parse);
	free(pathvalue);
	return (parsedpath);
}

/**
* getpath - gets the absolute path of a command
* @parsedpath: array of all path values
* @exe: string holding the command
* @src: path of current directory
*
* Return: absolute path
* NULL if command not found in any path
*/

char *getpath(char **parsedpath, char *exe, const char *src)
{
	int j = 0, k = 0, len;
	struct stat st;
	char *parsedpathcpy, *execpy;

	execpy = _strdup(exe);
	while (execpy[k] != '/' && execpy[k] != '\0')
	{ k++; }
	if (execpy[k] == '/')
	{ execpy = NULL; }

	while (parsedpath[j])
	{
		len = _strlen(parsedpath[j]) + _strlen(exe);
		parsedpathcpy = malloc((len + 2) * sizeof(char *));
		if (parsedpathcpy == NULL)
		{ free(parsedpathcpy), exit(1); }
		parsedpathcpy = _strcpy(parsedpathcpy, parsedpath[j]);
		chdir(parsedpath[j]);
		if (execpy != NULL)
		{
			if (stat(execpy, &st) == 0)
			{
				parsedpathcpy =  _strcat(parsedpathcpy, "/");
				parsedpathcpy = _strcat(parsedpathcpy, execpy);
				free(execpy);
				chdir(src);
				return (parsedpathcpy);
			}
		}
		free(parsedpathcpy);
		j++;
	}
	free(execpy);
	chdir(src);
	errno = 2;
	return (_strdup(parsedpath[j]));
}


