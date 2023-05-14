#include "monty.h"
#include <string.h>
#include <unistd.h>
/**
 * get_instructions - selects the correct function to
 *                     perform the opcode passed
 * @str: the string to check
 * @top: double pointer to the linked list
 * @line_number: line number of file
 * Return: success or failuree
 *
 */
int get_instructions(char *str, stack_t **top, unsigned int line_number)
{
	instruction_t opcodes[] = {
		{"push", push},
		{"pall", pall},
		{"pop", pop},
		{"nop", nop},
		{"swap", swap},
		{"add", add},
		{NULL, NULL}
	};
	int i = 0;

	while (opcodes[i].opcode != NULL)
	{
		if (strncmp(opcodes[i].opcode, str, 5) == 0)
		{
			opcodes[i].f(top, line_number);
			return (EXIT_SUCCESS);
		}
		else
			i++;
	}
	dprintf(STDERR_FILENO, "L%i: unknown instruction %s\n", line_number, str);
	exit(EXIT_FAILURE);
}