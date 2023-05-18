#include "main.h"

int main(int ac, char **av)
{
    char *prompt = "alx_shell:$ ";
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int interactive = isatty(STDIN_FILENO);

    (void)ac;

    while (1)
    {
        if (interactive) {
            printf("%s", prompt);
            fflush(stdout);
        }

        nchars_read = getline(&lineptr, &n, stdin);

        if (nchars_read == -1)
        {
            if (feof(stdin)) {
                printf("\n");
                free(lineptr);
                return 0;
            }
            perror("getline");
            free(lineptr);
            return -1;
        }

        char **argv = tokenize(lineptr, delim);
        execmd(argv);

        free_tokens(argv);

        if (!interactive) {
            free(lineptr);
            return 0;
        }
    }

    return 0;
}
