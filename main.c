#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * is_digit - function
 * @s: tha path to be analyzed
 * Description: a function that checks if a number is digit or not
 * Return: 0 on success 1 on failure
 */
int is_digit(char *s, unsigned int line_count, char *parameter)
{
	int n;
	int i;

	if (s == NULL)
		return (1);

	n = strlen(s);
	for (i = 0; i < n; i++)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_count, parameter);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
/**
 * get_name - function
 * @path: tha path to be analyzed
 * Description: a function to extract filename from path
 * Return: string on success
 */
char *get_name(char *path)
{
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
int global_variable = 1;
/**
 * getbuffer - function
 * @buffer: tha buffer oft the getline
 * Description: a function to analyse each line and use the right function
 * Return: nothing
 */
void getbuffer(char *buffer, stack_t **stack, unsigned int line_count)
{
	int i = 0;
	int y = 0;
	char *argv[10];
	char *token = NULL;

	if (buffer == NULL)
		exit(2);

	/*token = malloc(sizeof(char) * 1024);
	  if (!token)
	  exit(2);
	  */
	/*argv = malloc(sizeof(char *) * 1024);
	  if (!argv)
	  exit(2);*/
	instruction_t inst[] = {{"push", push}, {"pall", pall}, {NULL, 0}};

	token = strtok(buffer, " \n");
	while (token)
	{
		argv[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	for (y = 0; inst[y].opcode != NULL; y++)
	{
		if (argv[0] == NULL)
			break;
		if (strcmp(inst[y].opcode, argv[0]) == 0)
		{
			if (strcmp(argv[0], "push") == 0)
			{
				/*0s_digit(argv[1], line_count, inst[y].opcode);*/
				global_variable = atoi(argv[1]);
			}
			inst[y].f(stack, line_count);
		}
		/**
		 * else
		 {
		 printf("L%u: unknown instruction %s\n", line_count, inst[y].opcode);
		 exit(EXIT_FAILURE);
		 }
		 */
	}
}
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new = malloc(sizeof(stack_t));
	if (new == NULL)
		exit(2);

	if (!stack)
		exit(2);
	new->n = global_variable;

	new->next = (*stack);
	new->prev = NULL;

	if (*stack != NULL)
		(*stack)->prev = new;

	*stack = new;
	/*printf("%d", (*stack)->n);*/
}
void pall(stack_t **stack, unsigned int line_number)
{
	while (*stack)
	{
		printf("%d\n", (*stack)->n);
		*stack = (*stack)->next;
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
	char *fileName, *buffer = NULL;
	int line_count = 1;
	stack_t **st = NULL;
	st = malloc(sizeof(stack_t));
	if (!st)
		exit(2);

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
	fileOpen = fopen(fileName, "r");
	if (!(fileOpen))
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", fileName);
	}
	/* Get the first line of the file. */

	/* Loop through until we are done with the file. */
	while (getline(&buffer, &bufsize, fileOpen) >= 0)
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


		/* Show the line details */
		//printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s\n", line_count,
		//line_size, bufsize, buffer);

		/* Get the next line */
		/*printf("line_size\n");*/
		/*line_size = getline(&buffer, &line_size, fileOpen);*/
		getbuffer(buffer, st, line_count);
		line_count++;
	}
	fclose(fileOpen);
	return (0);
}

