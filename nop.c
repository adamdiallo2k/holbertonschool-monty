#include "monty.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/**
 * op_nop - function that doesn't do anything
 * @top: double pointer to the stack
 * @line_number: the line number where the opcode is called
 */
void nop(stack_t **top, unsigned int line_number)
{
	(void)top;
	(void)line_number;
}