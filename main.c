#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * get_name - function
 * @path: tha path to be analyzed
 * Description: a function to extract filename from path
 * Return: string on success
 */
char *get_name(char *path)
{
	stack_t **stack;
	char *token;
	char *temp;

	token = strtok(path, "/");
	while (token)
	{
		temp = strtok(NULL, "/");
		if (temp == NULL)
			break;
		token = temp;
	}
	return (token);
}
int global_variable;
/**
* getbuffer - function
* @buffer: tha buffer oft the getline
* Description: a function to analyse each line and use the right function
* Return: nothing
*/
void *getbuffer(char *buffer, stack_t *stack, int line_count)
{
	int i = 0;
	int y = 0;
	char **argv = NULL;
	char *token = NULL;

	token = malloc(sizeof(char) * 1024);
	if (!token)
		exit(2);
	argv = malloc(sizeof(char *) * 1024);
	if (!argv)
		exit(2);
	instruction_t inst[] = {{"push", push}, {"NULL", 0}};

	token = strtok(buffer, " \n");
	while (token)
	{
		argv[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	for (i = 0; argv[i] != NULL; i++)
	{
		for (y = 0; inst[y].opcode; y++)
		{
			if (strcmp(inst[y].opcode, argv[i]) == 0)
			{
				global_variable = atoi(argv[i + 1]);
				inst[y].f(&stack, line_count);
			}
		}
	}
}

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *h;
	stack_t *new = malloc(sizeof(stack_t));

	if (new == NULL)
		exit(2);

	new->n = global_variable;

	if (!*stack)
	{
		new->next = NULL;
		new->prev = NULL;
		*stack = new;
	}
	else
	{
	 h = *stack;

	while (h->next)
		h = h->next;

	if (h != NULL)
		h->prev = new;

	h->next = new;
	new->prev = h;
	new->next = NULL;
	}
}



/**
 * main - main function for monty interpreter
 * @argc: arg count
 * @argv: arg vector list
 * Return: 0 on success or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	FILE *fileOpen;
	size_t  bufsize;
	ssize_t line_size;
	char *fileName, *buffer = NULL;
	int line_count = 0;
	stack_t *st;

	/*handle error cases*/
	/**
	 *If the user does not give any file
	 *or more than one argument to your program,
	 *print the error message USAGE: monty file
	 *followed by a new line, and exit with the status EXIT_FAILURE
	 */
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	/**
	 *If, for any reason, it’s not possible to open the file,
	 *print the error message Error: Can't open file <file>,
	 *followed by a new line, and exit with the status EXIT_FAILURE
	 *where <file> is the name of the file
	 */
	/**
	 * so we need to extract the name of the file from the path
	 * using strtok
	 * create a function to extract the name
	 */
	fileName = get_name(argv[1]);
	printf("%s\n", fileName);
	fileOpen = fopen(fileName, "r");
	if (!(fileOpen))
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", fileName);
	}
	/* Get the first line of the file. */
	line_size = getline(&buffer, &bufsize, fileOpen);

	/* Loop through until we are done with the file. */
	while (line_size >= 0)
	{
		/**
		 *If the file contains an invalid instruction,
		 *print the error message L<line_number>:unknown instruction <opcode>,
		 *followed by a new line, and exit with the status EXIT_FAILURE
		 *where is the line number where the instruction appears.
		 *Line numbers always start at 1
		 */
		/**create a function
		 * to analyze the lines using strtok
		 * and compare the contents of the lines with the
		 * corresponding operations and functions
		 * using the given structure data type "instruction_t;"
		 */

		/* Increment our line count */
		line_count++;

		/* Show the line details */
		printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s\n", line_count,
				line_size, bufsize, buffer);

		/* Get the next line */
		line_size = getline(&buffer, &line_size, fileOpen);
		getbuffer(buffer, st,line_count);


	}
	free(buffer);
	buffer = NULL;
	fclose(fileOpen);
	return (0);

}
