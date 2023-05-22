#include "main.h"

/**
 * variableHandler - subsitute variables with their values
 * @argv: array of varibles of commands
 * Description: Replace the varibales with actual commands
 * Return: The void
 */

void variableHandler(char **argv)
{
	int index;
	char processString[10];
	char *envValue;

	for (index = 0; argv[index] != NULL; index++)
	{
		if (argv[index][0] == '$')
		{
			if (strcmp(argv[index], "$$") == 0)
			{
				sprintf(processString, "%d", getpid());
				free(argv[index]);
				argv[index] = strdup(processString);
			}
			else if (strcmp(argv[index], "$?") == 0)
			{
				envValue = getenv("?");
				free(argv[index]);

				if (envValue != NULL)
				{
					argv[index] = strdup(envValue);
				}
				else
				{
					argv[index] = strdup("");
				}
			}
			else
			{

			}
		}
	}
}
