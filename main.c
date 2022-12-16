#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
int global_variable = 1;
/**
 * is_digit - function
 * @s: tha path to be analyzed
 * @line_count: number of lines
 * Description: a function that checks if a number is digit or not
 * Return: 0 on success 1 on failure
 */
int is_digit(char *s, unsigned int line_count)
{
	int n;
	int i;
	int j;

	if (!s)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_count);
		exit(EXIT_FAILURE);
	}

	n = strlen(s);
	for (j = 1; j < n; j++)
	{
		if ((s[0] == '-') && (s[j] >= '0' && s[j] <= '9'))
			return (0);
	}
	for (i = 0; i < n; i++)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_count);
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
/**
 * getbuffer - function
 * @buffer: tha buffer oft the getline
 * @stack: double pointer
 * @line_count: number of line
 * Description: a function to analyse each line and use the right function
 * Return: nothing
 */
void getbuffer(char *buffer, stack_t **stack, unsigned int line_count)
{
	int i = 0;
	int y = 0;
	char *argv[64];
	char *token = NULL;
	instruction_t inst[] = {{"push", push}, {"pall", pall}, {"pint", pint},
		{"pop", pop}, {"swap", swap}, {NULL, 0}};

	if (buffer == NULL)
		exit(2);
	token = strtok(buffer, " \n");
	while (token)
	{
		argv[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	argv[i] = NULL;
	for (y = 0; inst[y].opcode != NULL; y++)
	{
		if (argv[0] == NULL)
			return;
		if (strcmp(inst[y].opcode, argv[0]) == 0)
		{
			if (strcmp(argv[0], "push") == 0)
			{
				is_digit(argv[1], line_count);
				global_variable = atoi(argv[1]);
			}
			inst[y].f(stack, line_count);
			return;
		}
	}

	if (inst[y].opcode == NULL)
		/* if we didnt find the user input it must be wrong*/
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_count, argv[0]);
		exit(EXIT_FAILURE);
	}
	free(token);
	token = NULL;
}
/**
 * push - function
 * @stack: double pointer
 * @line_number: number of line
 * Description: a function that pushes data
 * Return: nothing
 */
void push(stack_t **stack, unsigned int line_number)

{
	stack_t *new = malloc(sizeof(stack_t));
	if (new == NULL)
		exit(2);

	if (!(stack || *stack))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	if (stack == NULL)
		exit(2);

	new->n = global_variable;

	new->next = NULL;
	new->prev = NULL;

	if (*stack != NULL)
	{
		(*stack)->prev = new;
		new->next = (*stack);
	}

	*stack = new;
	/*printf("%d", (*stack)->n);*/
}
/**
 * pall - function
 * @stack: double pointer
 * @line_number: number of line
 * Description: a function to analyse each line and use the right function
 * Return: nothing
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *head = (*stack);

	if (!(stack || *stack))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	while (stack && *stack)
	{
		printf("%d\n", (*stack)->n);
		*stack = (*stack)->next;
	}
	*stack = head;
}
/**
 * pint - function
 * @stack: double pointer
 * @line_number: number of line
 * Description: a function that prints
 * Return: nothing
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%d: can't pint an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);

}
/**
 * pop - function
 * @stack: double pointer
 * @line_number: number of line
 * Description: a function that removes from the stack
 * Return: nothing
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *node;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	node = *stack;

	*stack = (*stack)->next;

	free(node);
	node = NULL;
}
/**
 * pop - function
 * @stack: double pointer
 * @line_number: number of line
 * Description: a function that removes from the stack
 * Return: nothing
 */
void swap(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
		exit(EXIT_FAILURE);
	if (!(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	/* declaration of variable */
	int node;
	stack_t *tmp;

	tmp = (*stack)->next;
	node = tmp->n;
	tmp->n = (*stack)->n;
	(*stack)->n = node;
}
/**
 * main - main function
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
	stack_t *tmp = NULL;

	st = malloc(sizeof(stack_t *));
	*st = NULL;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fileName = get_name(argv[1]);
	fileOpen = fopen(fileName, "r");
	if (!(fileOpen))
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", fileName);
		return (EXIT_FAILURE);
	}

	while (getline(&buffer, &bufsize, fileOpen) >= 0)
	{

		getbuffer(buffer, st, line_count);
		line_count++;
	}
	fclose(fileOpen);
	while (*st)
	{
		tmp = (*st);
		*st = (*st)->next;
		free(tmp);
		tmp = NULL;
	}
	free(st), free(buffer);
	buffer = NULL, st = NULL;
	return (0);
}
