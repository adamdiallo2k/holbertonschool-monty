#include "monty.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/**
 * op_pop - function that remove the first node onf the stack
 * @top: double pointer to the stack
 * @line_number: the line number where the opcode is called
 */

void pop(stack_t **top, unsigned int line_number)
{
	stack_t *tmp = *top;

	if (*top == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	*top = (*top)->next;
	free(tmp);

	if (*top != NULL)
		(*top)->prev = NULL;
}