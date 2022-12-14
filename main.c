#include "monty.h"
#include <stdio.h>
#include<string.h>
#include<ctype.h>
unsigned int LINE_NUMBER;
int is_digit(char *str)
{
	int i, status;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (status == 1)
		{
			break;
			printf("not digit");
			return (1);
		}
		while (isdigit(str[i]))
		{
			printf("%c", str[i]);

			if (isdigit(str[i + 1]))
			{
				status = 1;
			}
			i++;
		}
	}

	return (0);

}
void push(stack_t **stack, unsigned int line_number)
{
	printf("\nhi\n");
	/**
	  stack_t *h;
	  stack_t *new = malloc(sizeof(stack_t));

	  if (new == NULL)
	  exit(2);

	 *new->n = global_variable;

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
	 */
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

/**
 * buffer_analyzer - function
 * @buffer: tha buffer oft the getline
 * Description: a function to analyse each line and use the right function
 * Return: nothing
 */
void *buffer_analyzer(char *buffer)
{/*declare a pointer of type stack_t to access the n variable*/
	stack_t *stack = NULL;
	/* LINE_NUMBER should be a global variable, but i guess am using it wrong so its generating errors*/
	/*unsigned int LINE_NUMBER;*/
	int i, y, j = 0;
	y = 0;
	i = 0;
	char **argv = NULL;
	char *token = NULL;
	instruction_t inst[] = {{"push", push}, {0, NULL}};

	token = malloc(sizeof(char) * 1024);
	if (!token)
		exit(2);
	argv = malloc(sizeof(char *) * 1024);
	if (!argv)
		exit(2);
	token = strtok(buffer, " \n");
	while (token)
	{
		argv[i] = token;
		token = strtok(NULL, " \n");
		printf("%s\n", argv[i]);
		i++;
	}
	if (is_digit(argv[0]) == 0)
		inst[y].f(&stack, LINE_NUMBER);
	/*if (strcmp(inst[y].opcode, argv[y]) == 0)*/
	/*printf("%s", argv[i + 1]);*/
	/*stack->n = atoi(argv[i + 1]);*/
	free(token);
	token = NULL;
	free(argv);
	argv = NULL;
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

	/*unsigned int*/
	/*LINE_NUMBER = 0;*/

	/*int line_count = 0;*/
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fileName = get_name(argv[1]);
	printf("%s\n", fileName);
	fileOpen = fopen(fileName, "r");
	if (!(fileOpen))
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", fileName);
	}
	while (getline(&buffer, &bufsize, fileOpen) >= 0)
	{
		LINE_NUMBER++;
		buffer_analyzer(buffer);
	}
	free(buffer);
	buffer = NULL;
	fclose(fileOpen);
	return (0);

}
