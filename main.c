#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "alx_shell:$ ";
    char *lineptr = NULL; 
    char *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    int interactive;

    /* declaring void variables */
    (void)ac;

    /* Check if running in interactive mode */
    interactive = isatty(STDIN_FILENO);

    /* Create a loop for the shell's prompt */
    while (1)
    {
        /* Display prompt only in interactive mode */
        if (interactive) {
            printf("%s", prompt);
        }

        nchars_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (nchars_read == -1)
        {
            if (feof(stdin)) {  /* end of file reached (e.g., CTRL + D) */
                printf("\n");
                return (0);
            }
            perror("getline");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * (nchars_read + 1));
        if (lineptr_copy == NULL)
        {
            perror("malloc");
            return (-1);
        }
        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* execmd(argv); */

        /* execute the command */
        while (execmd(argv) == true)
        {
            if ((execve(argv[0], argv, NULL) == -1) != true)
            {
                fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, argv[0]);
                exit(EXIT_FAILURE);
            }
            else
            {
                execmd(argv);
            }
        }

        /* free up allocated memory */
        for (i = 0; i < num_tokens - 1; i++) {
            free(argv[i]);
        }
        free(argv);
        free(lineptr_copy);
        free(lineptr);
        lineptr = NULL;
        num_tokens = 0;

        /* Exit loop if not running in interactive mode */
        if (!interactive) {
            return 0;
        }
    }

    return (0);
}
