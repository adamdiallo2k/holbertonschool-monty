#include "monty.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>
char *value;
/**
 * op_push - function that pushes an element to the stack
 * @top: double pointer to the stack
 * @line_number: the line number where the opcode is called
 * Return: 0
 */
void push(stack_t **top, unsigned int line_number)
{
	stack_t *new = NULL;
	int element = 0;

	value = strtok(NULL, " \n\t");
	if (value == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number);
		whilefree(top);
		exit(EXIT_FAILURE);
	}

	if (_isdigit(value) == 1)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number);
		whilefree(top);
		exit(EXIT_FAILURE);
	}

	element = atoi(value);
	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(new);
		exit(EXIT_FAILURE);
	}

	new->n = element;
	if (*top)
		(*top)->prev = new;
	new->next = *top;
	new->prev = NULL;

	*top = new;
}