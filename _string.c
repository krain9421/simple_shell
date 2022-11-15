#include "main.h"
#include <stdio.h>

/**
* _strcat - concatenates two strings
* dest must be large enough to hold result
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
* dest must be large enough to hold result
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

/**
* _strlen - gets the length of a string
* @str: string
*
* Return: integer size of string
*/

int _strlen(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

/**
* _strdup - duplicates a string
* @src: source string
*
* Return: duplicate string
*/

char *_strdup(char *src)
{
	int src_size = 0, i = 0;
	static char *dup;
	/*char *dup_offset;*/

	if (src == NULL)
	{
		return (NULL);
	}

	src_size = _strlen(src);
	dup = malloc(sizeof(char) * (src_size + 1));

	if (dup == NULL)
	{
		free(dup);
		exit(1);
		/*return (NULL);*/
	}

	return (dup);
}

