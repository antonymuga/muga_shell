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

    (void)ac;

    interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive) {
            printf("%s", prompt);
        }

        nchars_read = getline(&lineptr, &n, stdin);

        if (nchars_read == -1)
        {
            if (feof(stdin)) {
                printf("\n");
                return (0);
            }
            perror("getline");
            return (-1);
        }

        lineptr_copy = malloc(sizeof(char) * (nchars_read + 1));
        if (lineptr_copy == NULL)
        {
            perror("malloc");
            return (-1);
        }

        strcpy(lineptr_copy, lineptr);

        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        char **argv_copy = malloc(sizeof(char *) * (num_tokens + 1));
        for (i = 0; i < num_tokens; i++) {
            argv_copy[i] = strdup(argv[i]);
        }
        argv_copy[num_tokens] = NULL;

        execmd(argv_copy);

        for (i = 0; i < num_tokens; i++) {
            free(argv_copy[i]);
        }
        free(argv_copy);
        free(lineptr_copy);
        free(lineptr);
        lineptr = NULL;
        num_tokens = 0;

        if (!interactive) {
            return 0;
        }
    }

    return (0);
}
