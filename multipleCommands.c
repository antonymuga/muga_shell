#include "main.h"

/**
 * executeCommands - Executes multiple commands separated by semicolons
 * @commands: input string containing multiple commands
 * Description: Tokenizes the input string based on semicolons,
 * executes each command individually using the runCommand function
 * Return: The void
 */
void executeCommands(char *commands)
{
    const char *delimiter = ";";
    char *token;
    char **args;
    int i;

    token = strtok(commands, delimiter);

    while (token != NULL)
    {
        /* Tokenize each command based on whitespace */
        const char *whitespace = " \t\n";
        char *arg;
        int numArgs = 0;

        args = malloc(sizeof(char *) * MAX_ARGS); /* MAX_ARGS is the maximum number of arguments expected */

        arg = strtok(token, whitespace);
        while (arg != NULL)
        {
            args[numArgs++] = arg;
            arg = strtok(NULL, whitespace);
        }
        args[numArgs] = NULL;

        /* Execute the command */
        runCommand(args);

        /* Free allocated memory */
        for (i = 0; i < numArgs; i++)
        {
            free(args[i]);
        }
        free(args);

        token = strtok(NULL, delimiter);
    }
}
