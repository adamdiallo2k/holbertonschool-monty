#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char *value;
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
	FILE *fp;
	stack_t *top = NULL;

	/* checks if there are exactly 2 arguments */
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		whilefree(&top);
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r"); /* opens the file */

	if (fp == NULL) /* if the file cannot be opened */
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		whilefree(&top);
		exit(EXIT_FAILURE);
	}
	read_line(fp);

	fclose(fp);
	whilefree(&top);
	return (0);
}