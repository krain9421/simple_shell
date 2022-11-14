#include "main.h"
#include <stdio.h>

/**
* main - program starts here
* @argc: argument counter
* @argv: argument vector
* @env: environment vector
*
* Return: int
*/

int main(int argc, char **argv, char **env)
{
	if (argc)
	{
		loopshell(argv, env);
	}

	return (0);
}

