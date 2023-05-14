#include "monty.h"
#include <string.h>

/**
 * read_line - function that reads line by line and
 *				call the opcode function
 * @fp: open file
 * Return: 0
 */
b
void read_line(FILE *fp)
{
	char line[MAX_LEN];
	stack_t *top = NULL;
	int line_number = 1;

	while (fgets(line, MAX_LEN, fp)) /* reads line by line */
	{
		value = strtok(line, "\n\t ");

		if (value == NULL)
		{
			line_number++;
			continue;
		}

		if (value[0] == '#')
		{
			line_number++;
			continue;
		}

		if (line[0] == '\n' && line[1] == '\0')
		{
			line_number++;
			continue;
		}
		else
		{
			get_instructions(value, &top, line_number);
			line_number++;
		}
	}

	whilefree(&top);
}