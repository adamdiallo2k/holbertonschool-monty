#include "monty.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * op_add - function that divides the second top element of
 *          the stack by the top element of the stack
 * @top: double pointer to the stack
 * @line_number: the line number where the opcode is called
 * Return: 0
 */

void add(stack_t **top, unsigned int line_number)
{
	int num1 = 0;
	int num2 = 0;
	int result = 0;
	stack_t *temp = NULL;

	if (*top == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*top)->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	num1 = (*top)->n;
	*top = (*top)->next;
	num2 = (*top)->n;

	result = num1 + num2;
	(*top)->n = result;

	temp = *top;

	free((*top)->prev);

	while (temp != NULL)
	{
		temp = temp->next;
	}
	free(temp);
}