#include "main.h"
#include <stdio.h>

/**
* _getenv - gets an environment variable
* @name: variable name
* @env: environment vector
*
* Return: string containing variable value
*/

char *_getenv(const char *name, char **env)
{
	int i = 0, j = 0;
	/*char *finalpath;*/

	while (env[i])
	{
		for (; name[j]; j++)
		{
			if (name[j] == env[i][j])
			{ continue; }
			else
			{ break; }
		}
		if (name[j] == '\0')
		{
			/*finalpath = _strdup(env[i] + _strlen(name) + 1);*/
			return (env[i] + _strlen(name) + 1);
		}
		i++;
	}
	return (NULL);
}

/**
* getpaths - stores all the path values in an array
* @env: environment vector
* Return: string array containing each path
*/

char **getpaths(char **env)
{
	char *parse, *pathvalue2, *pathvalue;
	int i = 0, sz = PARSESIZE;
	char **parsedpath;

	/* Getting the size of the array to hold paths */
	pathvalue = _getenv("PATH", env);
	pathvalue2 = _strdup(pathvalue);
	if (pathvalue2 == NULL)
	{ free(pathvalue2), exit(EXIT_FAILURE); }
	/**
	*pathvalue = _strdup(pathvalue2);
	*parse = strtok(pathvalue2, ":");
	*while (parse != NULL)
	*{
	*	parse = strtok(NULL, ":");
	*	sz++;
	*}
	*free(parse);
	*free(pathvalue2);
	*/
	parsedpath = malloc((sz + 0) * sizeof(char *));
	if (parsedpath == NULL)
	{ free(parsedpath), free(pathvalue2), exit(EXIT_FAILURE); }

	parse = strtok(pathvalue2, ":");
	while (parse != NULL)
	{
		parsedpath[i] = (parse);
		parse = strtok(NULL, ":");
		i++;
	}
	parsedpath[i] = NULL;
	free(parse);
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
		parsedpathcpy = malloc((len + 2) * sizeof(char));
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
	return (NULL);
}

