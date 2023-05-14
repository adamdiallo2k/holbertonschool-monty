#include "monty.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/**
 * op_swap - function that swaps the top 2 elements of the stack
 * @top: double pointer to the stack
 * @line_number: the line number where the opcode is called
 * Return:
 *  0
 */

void swap(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;
	int element;

	if (*top == NULL || (*top)->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n", line_number);
		whilefree(top);
		exit(EXIT_FAILURE);
	}

	tmp = (*top)->next;
	element = tmp->n;
	tmp->n = (*top)->n;
	(*top)->n = element;
}