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
	char *dup;

	if (src == NULL)
	{
		return (NULL);
	}

	src_size = _strlen(src);
	dup = malloc(sizeof(char) * (src_size + 1));

	if (dup == NULL)
	{
		free(dup);
		return (NULL);
	}

	while (src_size--)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';

	return (dup);
}

/**
* _strcmp - function compares two strings
* @s1: index string
* @s2: string to compare with
*
* Return: less than, equal to or
* greater than zero if S1 is
* lexicographically less than,
* equal to or greater than S2
*/

int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int cmp = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] == s2[i])
		{}
		else
		{
			cmp = s1[i] - s2[i];
			return (cmp);
		}
		i++;
	}

	return (cmp);
}

