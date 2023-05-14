#include "monty.h"

/**
 * whilefree - function that frees
 * @top: double pointer to the linked list
 */
void whilefree(stack_t **top)
{
	stack_t *temp = NULL;

	while (*top != NULL)
	{
		temp = (*top)->next;
		free(*top);
		*top = NULL;
		*top = temp;
	}
	free(*top);
}