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
			environ[i] += j + 1;
			return (environ[i]);
		}
		i++;
	}
	return (NULL);
}

