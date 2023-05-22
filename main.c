#include "main.h"

/**
 * main - program entry point
 * @ac: argument count
 * @argv: argument vector of commands
 * Description: This is the core logic of the shell
 * Return: status or exit code
 */

int main(int ac, char **argv)
{
    char *promptMessage = "alx_shell:$ ";
    char *cmdLiteral = NULL;
    char *cmdLiteralDup = NULL;
    size_t numOfChars = 0;
    ssize_t charsRead;
    const char *delimiter = " \n";
    int numOfTokens = 0;
    char *token;
    int index;
    int interactive;

    (void)ac;

    interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
        {
            printf("%s", promptMessage);
        }

        charsRead = getline(&cmdLiteral, &numOfChars, stdin);

        if (charsRead == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                return (0);
            }

            perror("getline");
            return (-1);
        }

        cmdLiteralDup = malloc(sizeof(char) * (charsRead + 1));

        if (cmdLiteralDup == NULL)
        {
            perror("malloc");
            return (-1);
        }

        strcpy(cmdLiteralDup, cmdLiteral);
        token = strtok(cmdLiteral, delimiter);

        while (token != NULL)
        {
            numOfTokens++;
            token = strtok(NULL, delimiter);
        }

        numOfTokens++;
        char *commands = malloc(sizeof(char) * (charsRead + 1));
        strcpy(commands, cmdLiteralDup);

        /* Execute multiple commands */
        executeCommands(commands);

        free(commands);
        free(cmdLiteralDup);
        free(cmdLiteral);
        cmdLiteral = NULL;
        numOfTokens = 0;

        if (!interactive)
        {
            return (0);
        }
    }

    return (0);
}
