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
			return (environ[i]);
		}
		i++;
	}
	return (NULL);
}

/**
* getpaths - stores all the paths in an array
*
* Return: string array containing each path
*/

char **getpaths()
{
	char *parse;
	char *pathvalue;
	char *value = malloc(1024 * sizeof(char));
	int i = 0;
	char **parsedpath;

	parsedpath = malloc(100 * sizeof(char *));
	if (parsedpath == NULL)
		exit(EXIT_FAILURE);

	pathvalue = _getenv("PATH");
	value = _strcpy(value, pathvalue);
	parse = strtok(value, "PATH= :");
	while (parse != NULL)
	{
		parsedpath[i++] = parse;
		parse = strtok(NULL, ":");
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
	int j = 0;
	struct stat st;

	while (parsedpath[j])
	{
		chdir(parsedpath[j]);
		if (exe)
		{
			if (stat(exe, &st) == 0)
			{
				parsedpath[j] =  _strcat(parsedpath[j], "/");
				parsedpath[j] = _strcat(parsedpath[j], exe);
				chdir(src);
				return (parsedpath[j]);
			}
		}
		j++;
	}
	chdir(src);
	return (parsedpath[j]);
}

/**
* _strcat - concatenates two strings
* @dest: destination string
* @src: source string
*
* Return: concatenated string
*/

char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strcpy - copies a string
* @dest: destination string
* @src: source string
*
* Return: copied string
*/

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

