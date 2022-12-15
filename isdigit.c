#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/**
 *main - function
 *
 *Description: a function to check if a string is a digit
 *Return: 0 on success 1 on erreur
 */
int main(void)
{
	char s[] = "000a23";
	/*char b = 0;*/
	int n = strlen(s);

	for (int i = 0; i < n; i++)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			printf("notdigit\n");
			return (1);
		}
	}
	printf("is digit\n");
	return (0);
}

