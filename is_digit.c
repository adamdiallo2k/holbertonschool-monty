#include "monty.h"
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
/**
 *_isdigit - check the code
 *@c: the character to check
 *Return: 1 if c is digit, 0 otherwise
 */

int _isdigit(char *c)
{
	int i = 0;

	for (; c[i] != '\0'; i++)
	{
		if (c[i] == '-')
			continue;
		if (isdigit(c[i]) == 0)
			return (1);
	}
	return (0);
}